
#include "OSGCommon.h"
#include "BillboardFactory.h"
using namespace osg;
using namespace BillboardExtension;

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
	ref_ptr<Image> image = osgDB::readImageFile("icon.png");// icon.png//Images/tree0.rgba 

	// scale to fit size.
	ref_ptr<PositionAttitudeTransform> pat = new PositionAttitudeTransform();
	pat->setScale(Vec3(5.0f, 5.0f, 5.0f));
	auto b1 = BillboardFactory::getInstance()->createBillboard(image, Vec3(5.0f, 0.0f, 0.0f));
	auto b2= BillboardFactory::getInstance()->createBillboard(NULL, Vec3(10.0f, 0.0f, 0.0f), Billboard::AXIAL_ROT, osg::Vec3(0.0f, 0.0f, 1.0f));
	//BillboardFactory::getInstance()->clearGeometryTextureCache();
	auto b3 = BillboardFactory::getInstance()->createBillboard();
	auto b4 = BillboardFactory::getInstance()->createBillboard();
	ref_ptr<Group> billboard = new Group();
	billboard->addChild(b1);
	billboard->addChild(b2);
	billboard->addChild(b3);
	billboard->addChild(b4);
	
	pat->addChild(billboard.get());

	root->addChild(pat.get());

	root->addChild(osgDB::readNodeFile("cow.osg"));

	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

	return 0;
}