/**\file
 * \brief Database-backed object
 *
 * Contains an abstraction for a typical database object with a numeric ID.
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

#if !defined(VERTHANDI_OBJECT_H)
#define VERTHANDI_OBJECT_H

#include <ef.gy/sqlite.h>

namespace verthandi
{
    /**\brief Database object with ID
     *
     * Base template for a typical database object with a numerical ID. This
     * base class provides the ID and keeps track of the database connection. It
     * also provides a flag for whether the current (derived) object is in a
     * valid state.
     *
     * \tparam db The database access class to use, e.g. efgy::database::sqlite
     */
    template <typename db>
    class object
    {
        public:
            /**\brief Construct with database and ID
             *
             * Constructor that uses an initialised instance of a database and
             * the ID of an object. The ID in an object<db> instance is
             * meaningless by itself and must be given meaning by any deriving
             * class.
             *
             * \param[out] pDatabase The database connection to use.
             * \param[in]  pID       The ID that the instance should represent.
             */
            object (db &pDatabase, const typename db::id &pID)
                : database(pDatabase), id(pID), valid(false) {}

            /**\brief Object ID
             *
             * The ID that an instance of the class should represent. An
             * instance of the 'project' class uses this field to store a
             * reference to the 'task.id' field in the database, for example.
             */
            typename db::id id;

            /**\brief Is the object's state valid?
             *
             * Set to 'true' when the object currently represents a valid object
             * as found in the database the last time the data was synchronised.
             * Reset to 'false' when the object is known to be invalid, e.g. if
             * the select to retrieve its data failed to return a row.
             */
            bool valid;

        protected:
            /**\brief Database connection
             *
             * Contains the proper, initialised database connection that the
             * constructor was called with.
             */
            db &database;
    };
};

#endif
