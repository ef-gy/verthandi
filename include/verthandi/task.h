/**\file
 * \brief Abstraction for a task
 *
 * Contains a C++ abstraction for a task, which is a single member of the tasks
 * table.
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

#if !defined(VERTHANDI_TASK_H)
#define VERTHANDI_TASK_H

#include <verthandi/object.h>

#include <ostream>
#include <string>

namespace verthandi
{
    /**\brief A project-specific task
     *
     * Contains a single row of the 'tasks' table in the database. The row is
     * identified by a numeric ID, which is why this class derives from the
     * verthandi::object template.
     *
     * \tparam db The database access class to use, e.g. efgy::database::sqlite
     */
    template <typename db>
    class task : public object<db>
    {
        public:
            /**\copydoc object<db>::object
             *
             * In instances of the task type, the pID is assumed to refer to the
             * contents of the tasks.id column, and the corresponding row is
             * automatically retrieved when an instance of the class is
             * initialised.
             */
            task (db &pDatabase, const typename db::id &pID)
                : object<db>(pDatabase, pID) { sync(); }

            /**\brief Task title
             *
             * Corresponds to the tasks.title field in the database.
             */
            std::string title;

            using object<db>::id;
            using object<db>::valid;

        protected:
            using object<db>::database;

            /**\brief Retrieve task data from database
             *
             * Selects the task's data from the database and stores the data in
             * the class instance.
             *
             * \returns 'true' if the task instance is now in a valid state,
             *          false otherwise.
             */
            bool sync (void)
            {
                typename db::statement select("select title from tasks where id=?1", database);
                select.bind(1, id);
                if (select.step() && select.row)
                {
                    select.get(0, title);
                    return (valid = true);
                }
                return (valid = false);
            }
    };

    /**\brief Serialise task to stream
     *
     * Writes an XML representation of a task to a C++ stream object.
     *
     * \tparam C  Character type of the stream.
     * \tparam db Database type of the task instance.
     *
     * \param[out] out The stream to write to.
     * \param[in]  p   The task instance to write to the stream.
     *
     * \returns A reference to the 'out' parameter, as is customary with C++
     *          streams.
     */
    template <typename C, typename db>
    efgy::render::oxmlstream<C> operator << (efgy::render::oxmlstream<C> out, const task<db> &p)
    {
        if (!p.valid)
        {
            out.stream << "<task id='" << p.id << "' status='invalid'/>";
        }
        else
        {
            out.stream << "<task id='" << p.id << "' name='" << p.title << "'/>";
        }
        return out;
    }
};

#endif
