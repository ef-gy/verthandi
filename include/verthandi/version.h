/**\file
 * \brief Version information
 *
 * Contains Verthandi's version number and assorted pieces of documentation that
 * didn't quite fit in anywhere else.
 *
 * \copyright
 * Copyright (c) 2013-2014, Verthandi Project Members
 * \copyright
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * \copyright
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * \copyright
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * \see Project Documentation: http://ef.gy/documentation/verthandi
 * \see Project Source Code: http://github.com/machinelady/verthandi.git
 */

#if !defined(VERTHANDI_VERSION_H)
#define VERTHANDI_VERSION_H

/**\dir include/verthandi
 * \brief Verthandi template code
 *
 * Contains headers that implement frontend and business logic of Verthandi;
 * Verthandi uses libefgy, and just like that library its code is also contained
 * in C++ template headers.
 */

/**\brief Library namespace for the Verthandi project
 *
 * This namespace contains all of the classes and functions that make up the
 * business logic in Verthandi.
 */
namespace verthandi
{
    /**\brief Library Version
     *
     * This is the library's version number. Verthandi uses a very simple,
     * single-integer versioning scheme: whenever a new version is released,
     * this number is increased by one and used until the next release.
     */
    static const unsigned int version = 1;
};

#endif
