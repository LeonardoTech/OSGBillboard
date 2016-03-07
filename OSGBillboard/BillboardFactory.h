#pragma once
#include <osg/Object>
#include <osg/Billboard>
#include "OSGCommon.h"
namespace BillboardExtension
{
	osg::ref_ptr<osg::Geometry> createQuad();

	class BillboardFactory : public osg::Object
	{
	public:
		// 获取单件实例
		static osg::ref_ptr<BillboardFactory> getInstance();

		// 创建广告牌
		// @param image: 广告牌纹理
		// 						设置一次后，后续调用此函数时就直接使用上一次的几何图形。
		// @param position: 广告牌位置
		// @param mode: 广告牌类型
		// @param axis: 广告牌围绕哪个轴旋转（仅 Billboard::AXIAL_ROT 有效）
		// @param geometry: 广告牌的几何图形
		// 							  默认为边长为2的方片。
		// 							  设置一次后，后续调用此函数时就直接使用上一次的几何图形。
		osg::ref_ptr<osg::Billboard> createBillboard(osg::Image *image = NULL, osg::Vec3 position = osg::Vec3(0, 0, 0), osg::Billboard::Mode mode = osg::Billboard::POINT_ROT_EYE, osg::Vec3 axis = osg::Vec3(0.0f, 0.0f, 0.0f), osg::Geometry* geometry = NULL);
		

#pragma region override

		/** Copy constructor using CopyOp to manage deep vs shallow copy. */
		BillboardFactory(const BillboardFactory& geometry, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

		/** Clone the type of an object, with Object* return type.
		Must be defined by derived classes.*/
		virtual Object* cloneType() const override;

		/** Clone an object, with Object* return type.
		Must be defined by derived classes.*/
		virtual Object* clone(const osg::CopyOp&) const override;

		/** return the name of the object's library. Must be defined
		by derived classes. The OpenSceneGraph convention is that the
		namespace of a library is the same as the library name.*/
		virtual const char* libraryName() const override;

		/** return the name of the object's class type. Must be defined
		by derived classes.*/
		virtual const char* className() const override;

#pragma endregion

	protected:
		BillboardFactory();

		static osg::ref_ptr<BillboardFactory> m_instance;

		osg::ref_ptr<osg::Geometry> m_geometry;
	};
}