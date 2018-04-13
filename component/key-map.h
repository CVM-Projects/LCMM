#pragma once
#include "lcmm.h"
#include <map>
#include <deque>
#include <vector>
#include <cassert>

namespace LCMM
{
	namespace Component
	{
		class KeyMap
		{

			class shared_ptr
			{
			public:
				shared_ptr() = default;

				explicit shared_ptr(KeyMap &mmml, void *data)
					: mmml(&mmml), index(mmml.insert(data)) {}

				~shared_ptr() {
					if (mmml) {
						if (mmml->dec_count(index)) {
							mmml->destory(index);
						}
					}
				}

				shared_ptr(const shared_ptr &sp)
					: mmml(sp.mmml), index(sp.index) {
					mmml->inc_count(index);
				}

				shared_ptr& operator=(const shared_ptr &sp) {
					mmml = sp.mmml;
					index = sp.index;
					mmml->inc_count(index);
					return *this;
				}

				void* get() const {
					return mmml->get(index);
				}
				void* operator->() const {
					return get();
				}

			private:
				KeyMap * mmml = nullptr;
				size_t index = 0;
			};

			struct Data {
				void *data = nullptr;
				size_t counter = 0;
			};

		public:
			KeyMap() = default;
			~KeyMap() {
				assert(_keymap.empty());
			}

			size_t insert(void *dat) {
				auto iter = _keymap.find(dat);
				if (iter != _keymap.end()) {
					return iter->second;
				}
				else {
					if (_allocable_index.empty()) {
						size_t id = _data.size();
						_data.push_back(Data { dat, 1 });
						_keymap[dat] = id;
						return id;
					}
					else {
						size_t id = _allocable_index.front();
						_keymap[dat] = id;
						_data[id] = Data { dat, 1 };
						_allocable_index.pop_front();
						return id;
					}
				}
			}

			void destory(size_t index, void(*func_free)(void*) = std::free) {
				void *ptr = _data[index].data;
				func_free(ptr); // Free
				_allocable_index.push_back(index);
				_keymap.erase(ptr);
			}

			void inc_count(size_t index) {
				_data[index].counter++;
			}
			bool dec_count(size_t index) {
				_data[index].counter--;
				return _data[index].counter == 0;
			}
			void* get(size_t index) const {
				return _data.at(index).data;
			}

		private:
			std::map<void*, size_t> _keymap;
			std::vector<Data> _data;
			std::deque<size_t> _allocable_index;
		};
	}
}
