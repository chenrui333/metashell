
// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2015, Andras Kucsma (andras.kucsma@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <metashell/data/type_or_code_or_error.hpp>

#include <cassert>
#include <variant>

namespace metashell
{
  namespace data
  {

    type_or_code_or_error::type_or_code_or_error() : data(blank{}) {}

    type_or_code_or_error::type_or_code_or_error(const type_type& t) : data(t)
    {
    }

    type_or_code_or_error::type_or_code_or_error(const code_type& t) : data(t)
    {
    }

    type_or_code_or_error::type_or_code_or_error(const error_type& e) : data(e)
    {
    }

    type_or_code_or_error type_or_code_or_error::make_none()
    {
      return type_or_code_or_error();
    }

    type_or_code_or_error type_or_code_or_error::make_type(const type_type& t)
    {
      return type_or_code_or_error(t);
    }

    type_or_code_or_error type_or_code_or_error::make_error(const error_type& e)
    {
      return type_or_code_or_error(e);
    }

    bool type_or_code_or_error::is_none() const
    {
      return std::get_if<blank>(&data) != nullptr;
    }

    bool type_or_code_or_error::is_type() const
    {
      return std::get_if<type_type>(&data) != nullptr;
    }

    bool type_or_code_or_error::is_code() const
    {
      return std::get_if<code_type>(&data) != nullptr;
    }

    bool type_or_code_or_error::is_error() const
    {
      return std::get_if<error_type>(&data) != nullptr;
    }

    const type_or_code_or_error::type_type&
    type_or_code_or_error::get_type() const
    {
      assert(is_type());
      return std::get<type_type>(data);
    }

    const type_or_code_or_error::code_type&
    type_or_code_or_error::get_code() const
    {
      assert(is_code());
      return std::get<code_type>(data);
    }

    const type_or_code_or_error::error_type&
    type_or_code_or_error::get_error() const
    {
      assert(is_error());
      return std::get<error_type>(data);
    }

    bool
    type_or_code_or_error::operator==(const type_or_code_or_error& other) const
    {
      return data == other.data;
    }

    std::ostream& operator<<(std::ostream& os, const type_or_code_or_error& te)
    {
      if (te.is_type())
      {
        os << "type[" << te.get_type() << "]";
      }
      else if (te.is_code())
      {
        os << "code[" << te.get_code() << "]";
      }
      else if (te.is_error())
      {
        os << "error[" << te.get_error() << "]";
      }
      else
      {
        os << "none[]";
      }
      return os;
    }
  } // namespace data
} // namespace metashell
