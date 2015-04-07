
#include "OSGCommon.h"
using namespace osg;

osg::ref_ptr<osg::Geometry> createQuad()
{
	// create quad
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// setup vertexes
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	// setup normals
	ref_ptr<Vec3Array> normal = new Vec3Array();
	normal->push_back(Vec3(1.0f, 0.0f, 0.0f) ^ Vec3(0.0f, 0.0f, 1.0f));

	geom->setNormalArray(normal.get());
	geom->setNormalBinding(Geometry::BIND_OVERALL);

	// setup texture coordinates.
	ref_ptr<Vec2Array> vt = new Vec2Array();
	vt->push_back(Vec2(0.0f, 0.0f));
	vt->push_back(Vec2(1.0f, 0.0f));
	vt->push_back(Vec2(1.0f, 1.0f));
	vt->push_back(Vec2(0.0f, 1.0f));

	geom->setTexCoordArray(0, vt.get());

	// draw quad
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	return geom;
}

ref_ptr<Node> creatBillboardTree(ref_ptr<Image> image)
{
	// create quad.
	ref_ptr<Geometry> geometry = createQuad();

	if (image.get())
	{
		// state property object
		ref_ptr<StateSet> stateset = new StateSet();

		// create a texture2d property object
		ref_ptr<Texture2D> texture = new Texture2D();
		// relate image
		texture->setImage(image.get());

		// relate texture2d object, the default value of the third param is ON.
		stateset->setTextureAttributeAndModes(0, texture, StateAttribute::ON);

		// enable blending
		stateset->setMode(GL_BLEND, StateAttribute::ON);

		// close lighting
		stateset->setMode(GL_LIGHTING, StateAttribute::OFF);

		geometry->setStateSet(stateset.get());
	}

	// create billboard object.
	ref_ptr<Billboard> billboard1 = new Billboard();

	// set ROT_EYE rotation mode.
	billboard1->setMode(Billboard::POINT_ROT_EYE);

	// add Drawable, and set its location, the default position is Vec3(0,0f, 0.0f, 0.0f)
	billboard1->addDrawable(geometry.get(), Vec3(5.0f, 0.0f, 0.0f));

	ref_ptr<Billboard> billboard2 = new Billboard();

	// set rotation mode to AXIAL_ROT, thus setting rotation axes is needed.
	billboard2->setMode(Billboard::AXIAL_ROT);

	// set rotation axes.
	billboard2->setAxis(Vec3(0.0f, 0.0f, 1.0f));
	billboard2->addDrawable(geometry.get(), Vec3(10.0f, 0.0f, 0.0f));

	ref_ptr<Group> billboard = new Group();
	billboard->addChild(billboard1.get());
	billboard->addChild(billboard2.get());

	return billboard.get();
}

int main()
{
	ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	ref_ptr<osg::Group> root = new osg::Group();

	// read image.
	ref_ptr<Image> image = osgDB::readImageFile("Bitmap.bmp");//Images/tree0.rgba

	// scale to fit size.
	ref_ptr<PositionAttitudeTransform> pat = new PositionAttitudeTransform();
	pat->setScale(Vec3(5.0f, 5.0f, 5.0f));
	pat->addChild(creatBillboardTree(image.get()));

	root->addChild(pat.get());

	root->addChild(osgDB::readNodeFile("cow.osg"));

	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

	return 0;
}