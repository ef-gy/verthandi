/**\file
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

#include <ef.gy/sqlite.h>

#include <string>
#include <ostream>

namespace verthandi
{
    template <typename db>
    class task
    {
        public:
            task (db &pDatabase, typename db::id pID)
                : database(pDatabase), id(pID) { sync(); }

            typename db::id id;
            std::string name;
            bool valid;

        protected:
            db &database;

            bool sync (void)
            {
                typename db::statement select("select title from tasks where id=?1", database);
                select.bind(1, id);
                if (select.step() && select.row)
                {
                    select.get(0, name);
                    return (valid = true);
                }
                return (valid = false);
            }
    };

    template <typename C, typename db>
    std::basic_ostream<C> &operator << (std::basic_ostream<C> &out, const task<db> &p)
    {
        return p.valid ? out << "<task id='" << p.id << "' name='" << p.name << "'/>"
                       : out << "<task id='" << p.id << "' status='invalid'/>";
    }
};

#endif