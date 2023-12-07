/*
 * MIT License https://github.com/Android1337/crycall/blob/main/LICENSE
 *
 * Copyright (c) 2023 Android1337
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CRYCALL_HPP
#define CRYCALL_HPP
#include <memory> // std::unique_ptr

namespace cryc
{
	template <typename ret_type>
	class cryCall {
	public:
		template <typename func_type>
		cryCall(func_type&& func) : storage(new cryHolder<func_type>(std::forward<func_type>(func))) {}

		ret_type operator()() const {
			return storage->invoke();
		}

	private:
		struct cryBase {
			virtual ret_type invoke() const = 0;
			virtual ~cryBase() = default;
		};

		template <typename func_type>
		struct cryHolder : cryBase {
			func_type func;

			cryHolder(func_type&& f) : func(std::forward<func_type>(f)) {}

			ret_type invoke() const override {
				return func();
			}
		};

		std::unique_ptr<cryBase> storage;
	};
}

#define crycall(ret_type, func, ...) [&]() { \
    cryc::cryCall<ret_type> f([&]() { \
        return func(__VA_ARGS__); \
    }); \
    return f(); \
}()

#define crycall_virtual(ret_type, _this, idx, ...) [&]() { \
    ret_type (*func)(__int64, ...); \
    func = decltype(func)(*(__int64*)(*(__int64*)__int64(_this) + (idx * sizeof(__int64)))); \
    cryc::cryCall<ret_type> f([&]() { \
        return func(__int64(_this), __VA_ARGS__); \
    }); \
    return f(); \
}()

#endif // include guard
