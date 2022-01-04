#!/usr/bin/env python
#
# Python-bindings message_table_resource type test script
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


class MessageTableResourceTypeTests(unittest.TestCase):
  """Tests the message_table_resource type."""

  _TEST_DATA = bytes(bytearray([
      0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
      0x1c, 0x00, 0x00, 0x00, 0xe8, 0x03, 0x00, 0x00, 0xe8, 0x03, 0x00, 0x00,
      0x54, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x43, 0x61, 0x74, 0x65,
      0x67, 0x6f, 0x72, 0x79, 0x0d, 0x0a, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
      0x4d, 0x79, 0x20, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x77,
      0x69, 0x74, 0x68, 0x20, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x65, 0x74, 0x65,
      0x72, 0x73, 0x20, 0x25, 0x31, 0x20, 0x25, 0x32, 0x2e, 0x0d, 0x0a, 0x00,
      0x24, 0x00, 0x00, 0x00, 0x4d, 0x79, 0x20, 0x6d, 0x65, 0x73, 0x73, 0x61,
      0x67, 0x65, 0x20, 0x77, 0x69, 0x74, 0x68, 0x6f, 0x75, 0x74, 0x20, 0x70,
      0x61, 0x72, 0x61, 0x6d, 0x65, 0x74, 0x65, 0x72, 0x73, 0x0d, 0x0a, 0x00]))

  def test_copy_from_byte_stream(self):
    """Tests the copy_from_byte_stream function."""
    message_table_resource = pywrc.message_table_resource()
    message_table_resource.copy_from_byte_stream(self._TEST_DATA)

    with self.assertRaises(TypeError):
      message_table_resource.copy_from_byte_stream(None)

    with self.assertRaises(IOError):
      message_table_resource.copy_from_byte_stream(b'')

    with self.assertRaises(RuntimeError):
      message_table_resource.copy_from_byte_stream(
          self._TEST_DATA, codepage='bogus')

  def test_get_number_of_messages(self):
    """Tests the get_number_of_messages function."""
    message_table_resource = pywrc.message_table_resource()
    message_table_resource.copy_from_byte_stream(self._TEST_DATA)

    number_of_messages = message_table_resource.get_number_of_messages()
    self.assertEqual(number_of_messages, 3)

  def test_get_message_identifier(self):
    """Tests the get_message_identifier function."""
    message_table_resource = pywrc.message_table_resource()
    message_table_resource.copy_from_byte_stream(self._TEST_DATA)

    message_identifier = message_table_resource.get_message_identifier(2)
    self.assertEqual(message_identifier, 0x000003e8)

  def test_get_string(self):
    """Tests the get_string function."""
    message_table_resource = pywrc.message_table_resource()
    message_table_resource.copy_from_byte_stream(self._TEST_DATA)

    string = message_table_resource.get_string(2)
    self.assertEqual(string, 'My message without parameters\r\n')

  def test_get_string_by_message_identifier(self):
    """Tests the get_string_by_message_identifier function."""
    message_table_resource = pywrc.message_table_resource()
    message_table_resource.copy_from_byte_stream(self._TEST_DATA)

    string = message_table_resource.get_string_by_message_identifier(0x000003e8)
    self.assertEqual(string, 'My message without parameters\r\n')


if __name__ == "__main__":
  unittest.main(verbosity=2)
