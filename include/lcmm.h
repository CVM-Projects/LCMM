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

		friend class MemoryManager;
	};

	class MemoryManager
	{
	public:
		void Alloc(Object &object) {
			assert(object.lcmm_info.restype == RT_None);
			object.lcmm_info.restype = RT_Owner;
		}
		void Delete(Object *object) {

		}

	private:
		std::list<Object*> owners;
	};
}

#endif
