// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_ADDRESS_FIELD_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_ADDRESS_FIELD_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/autofill/core/browser/autofill_type.h"
#include "components/autofill/core/browser/form_field.h"

namespace autofill {

class AutofillField;
class AutofillScanner;

class AddressField : public FormField {
 public:
  static scoped_ptr<FormField> Parse(AutofillScanner* scanner);

 protected:
  // FormField:
  bool ClassifyField(ServerFieldTypeMap* map) const override;

 private:
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseOneLineAddress);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseTwoLineAddress);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseThreeLineAddress);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseStreetAddressFromTextArea);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseCity);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseState);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseZip);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseStateAndZipOneLabel);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseCountry);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseTwoLineAddressMissingLabel);
  FRIEND_TEST_ALL_PREFIXES(AddressFieldTest, ParseCompany);

  static const int kZipCodeMatchType;
  static const int kCityMatchType;
  static const int kStateMatchType;

  AddressField();

  bool ParseCompany(AutofillScanner* scanner);
  bool ParseAddressLines(AutofillScanner* scanner);
  bool ParseCountry(AutofillScanner* scanner);
  bool ParseZipCode(AutofillScanner* scanner);
  bool ParseCity(AutofillScanner* scanner);
  bool ParseState(AutofillScanner* scanner);

  // Parses the current field pointed to by |scanner|, if it exists, and tries
  // to figure out whether the field's type: city, state, zip, or none of those.
  bool ParseCityStateZipCode(AutofillScanner* scanner);

  // Run matches on the name and label separately. If the return result is
  // RESULT_MATCH_NAME_LABEL, then |scanner| advances and the field is set.
  // Otherwise |scanner| rewinds and the field is cleared.
  ParseNameLabelResult ParseNameAndLabelForZipCode(AutofillScanner* scanner);
  ParseNameLabelResult ParseNameAndLabelForCity(AutofillScanner* scanner);
  ParseNameLabelResult ParseNameAndLabelForState(AutofillScanner* scanner);

  AutofillField* company_;
  AutofillField* address1_;
  AutofillField* address2_;
  AutofillField* address3_;
  AutofillField* street_address_;
  AutofillField* city_;
  AutofillField* state_;
  AutofillField* zip_;
  AutofillField* zip4_;  // optional ZIP+4; we don't fill this yet.
  AutofillField* country_;

  DISALLOW_COPY_AND_ASSIGN(AddressField);
};

}  // namespace autofill

#endif  // COMPONENTS_AUTOFILL_CORE_BROWSER_ADDRESS_FIELD_H_
