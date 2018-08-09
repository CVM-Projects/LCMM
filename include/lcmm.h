#pragma once

#ifndef _LCMM_H_
#define _LCMM_H_
#include <list>
#include <cassert>

namespace LCMM
{
	enum ResourceType {
		RT_None = 0,      // None resource               [Default]
		RT_Owner,         // Owner of the resource                 :  A -> B
		RT_Refer,         // Refer from the resource's owner       :  A <- B
		RT_Share,         // All are owners                        :  A <-> B
	};

	struct Info
	{
		ResourceType restype = RT_None;
	};

	class Object
	{
	protected:
		Info lcmm_info;
		const Object *lcmm_refer = nullptr;

		void set_refer(const Object &refobj) {
			lcmm_refer = &refobj;
		}
		void set_restype(ResourceType type) {
			lcmm_info.restype = type;
		}
		bool is(ResourceType type) const {
			return lcmm_info.restype == type;
		}
		bool isnone() const {
			return is(RT_None);
		}
		ResourceType restype() const {
			return lcmm_info.restype;
		}
		const Object& refer() const {
			return *lcmm_refer;
		}

		friend class MemoryManager;
	};

	class MemoryManager
	{
	public:
		void Alloc(Object &object) {
			assert(object.isnone());
			object.set_restype(RT_Owner);
		}
		void Refer(Object &object, const Object &refobj) {
			assert(object.isnone());
			assert(!refobj.isnone());
			object.set_restype(RT_Refer);
			switch (refobj.restype()) {
			case RT_Refer:
			case RT_Share:
				object.set_refer(refobj.refer());
				break;
			case RT_Owner:
				object.set_refer(refobj);
				break;
			default:
				assert(false);
				break;
			}
		}
		void Delete(Object &object) {
			switch (object.restype()) {
			case RT_None:
				break;
			case RT_Owner:
				break;
			case RT_Refer:
			case RT_Share:
				break;
			default:
				assert(false);
				break;
			}
		}

	private:
		std::list<Object*> owners;
		std::list<Object*> shared_hosts;
	};
}

#endif
