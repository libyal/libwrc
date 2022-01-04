#!/usr/bin/env python
#
# Python-bindings string_table_resource type test script
#
# Copyright (C) 2011-2021, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import unittest

import pywrc


class StringTableResourceTypeTests(unittest.TestCase):
  """Tests the string_table_resource type."""

  _TEST_DATA = bytes(bytearray([
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x4d, 0x00, 0x79, 0x00, 0x20, 0x00,
      0x73, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00]))

  def test_copy_from_byte_stream(self):
    """Tests the copy_from_byte_stream function."""
    string_table_resource = pywrc.string_table_resource()
    string_table_resource.copy_from_byte_stream(self._TEST_DATA, 63)

    with self.assertRaises(TypeError):
      string_table_resource.copy_from_byte_stream(None, 63)

    with self.assertRaises(IOError):
      string_table_resource.copy_from_byte_stream(b'', 63)

  def test_get_number_of_strings(self):
    """Tests the get_number_of_strings function."""
    string_table_resource = pywrc.string_table_resource()
    string_table_resource.copy_from_byte_stream(self._TEST_DATA, 63)

    number_of_strings = string_table_resource.get_number_of_strings()
    self.assertEqual(number_of_strings, 1)

  def test_get_string_identifier(self):
    """Tests the get_string_identifier function."""
    string_table_resource = pywrc.string_table_resource()
    string_table_resource.copy_from_byte_stream(self._TEST_DATA, 63)

    string_identifier = string_table_resource.get_string_identifier(0)
    self.assertEqual(string_identifier, 0x000003e8)

  def test_get_string(self):
    """Tests the get_string function."""
    string_table_resource = pywrc.string_table_resource()
    string_table_resource.copy_from_byte_stream(self._TEST_DATA, 63)

    string = string_table_resource.get_string(0)
    self.assertEqual(string, 'My string')

  def test_get_string_by_string_identifier(self):
    """Tests the get_string_by_string_identifier function."""
    string_table_resource = pywrc.string_table_resource()
    string_table_resource.copy_from_byte_stream(self._TEST_DATA, 63)

    string = string_table_resource.get_string_by_string_identifier(0x000003e8)
    self.assertEqual(string, 'My string')


if __name__ == "__main__":
  unittest.main(verbosity=2)
