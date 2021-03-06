/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2017 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#include "util/time.hpp"

#include "boost-test.hpp"

namespace ndn {
namespace time {
namespace tests {

BOOST_AUTO_TEST_SUITE(Util)
BOOST_AUTO_TEST_SUITE(TestTime)

BOOST_AUTO_TEST_CASE(SystemClock)
{
  system_clock::TimePoint value = system_clock::now();
  system_clock::TimePoint referenceTime = fromUnixTimestamp(milliseconds(1390966967032LL));

  BOOST_CHECK_GT(value, referenceTime);

  BOOST_CHECK_EQUAL(toIsoString(referenceTime), "20140129T034247.032000");
  BOOST_CHECK_EQUAL(toString(referenceTime), "2014-01-29 03:42:47");
  BOOST_CHECK_EQUAL(toString(referenceTime), "2014-01-29 03:42:47");

  // Unfortunately, not all systems has lv_LV locale installed :(
  // BOOST_CHECK_EQUAL(toString(referenceTime, "%Y. gada %d. %B",
  //                                  std::locale("lv_LV.UTF-8")),
  //                   "2014. gada 29. Janvāris");

  BOOST_CHECK_EQUAL(toString(referenceTime, "%Y -- %d -- %B",
                                   std::locale("C")),
                    "2014 -- 29 -- January");

  BOOST_CHECK_EQUAL(fromIsoString("20140129T034247.032000"), referenceTime);
  BOOST_CHECK_EQUAL(fromIsoString("20140129T034247.032000Z"), referenceTime);
  BOOST_CHECK_EQUAL(fromString("2014-01-29 03:42:47"),
                    fromUnixTimestamp(seconds(1390966967)));

  // Unfortunately, not all systems has lv_LV locale installed :(
  // BOOST_CHECK_EQUAL(fromString("2014. gada 29. Janvāris", "%Y. gada %d. %B",
  //                                    std::locale("lv_LV.UTF-8")),
  //                   fromUnixTimestamp(seconds(1390953600)));

  BOOST_CHECK_EQUAL(fromString("2014 -- 29 -- January", "%Y -- %d -- %B",
                                     std::locale("C")),
                    fromUnixTimestamp(seconds(1390953600)));
}

BOOST_AUTO_TEST_CASE(SteadyClock)
{
  steady_clock::TimePoint oldValue = steady_clock::now();
  usleep(100);
  steady_clock::TimePoint newValue = steady_clock::now();

  BOOST_CHECK_GT(newValue, oldValue);
}

BOOST_AUTO_TEST_CASE(Abs)
{
  BOOST_CHECK_EQUAL(abs(nanoseconds(24422)), nanoseconds(24422));
  BOOST_CHECK_EQUAL(abs(microseconds(0)), microseconds(0));
  BOOST_CHECK_EQUAL(abs(milliseconds(-15583)), milliseconds(15583));
}

BOOST_AUTO_TEST_CASE(LargeDates)
{
  system_clock::TimePoint value = fromUnixTimestamp(milliseconds(1390966967032LL));
  BOOST_CHECK_EQUAL(toIsoString(value), "20140129T034247.032000");

  value += days(365 * 100 + 25 - 1); // 36524 days
  BOOST_CHECK_EQUAL(toIsoString(value), "21140129T034247.032000");
}

BOOST_AUTO_TEST_SUITE_END() // TestTime
BOOST_AUTO_TEST_SUITE_END() // Util

} // namespace tests
} // namespace time
} // namespace ndn
