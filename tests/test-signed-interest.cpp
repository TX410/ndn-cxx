/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Yingdi Yu <yingdi0@cs.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#include <boost/test/unit_test.hpp>

#include "security/key-chain.hpp"
#include "security/validator.hpp"
#include <iostream>

using namespace std;
namespace ndn {

BOOST_AUTO_TEST_SUITE(TestSignedInterest)

BOOST_AUTO_TEST_CASE (SignVerify)
{
  KeyChainImpl<SecPublicInfoSqlite3, SecTpmFile> keyChain;

  Name identityName("/TestSignedInterest/SignVerify");
  Name certificateName;
  BOOST_REQUIRE_NO_THROW(certificateName = keyChain.createIdentity(identityName));

  Interest interest("/TestSignedInterest/SignVerify/Interest1");
  keyChain.signByIdentity(interest, identityName);
  
  Block interestBlock(interest.wireEncode().wire(), interest.wireEncode().size());

  Interest interest2;
  interest2.wireDecode(interestBlock);
  
  shared_ptr<PublicKey> publicKey = keyChain.getPublicKeyFromTpm(keyChain.getDefaultKeyNameForIdentity(identityName));
  bool result = Validator::verifySignature(interest2, *publicKey);
  
  BOOST_CHECK_EQUAL(result, true);

  BOOST_CHECK_NO_THROW(keyChain.deleteIdentity(identityName));
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace ndn
