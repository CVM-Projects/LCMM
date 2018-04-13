#pragma once

#ifndef _LCMM_H_
#define _LCMM_H_

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

	class MemoryManager;
}

#endif
