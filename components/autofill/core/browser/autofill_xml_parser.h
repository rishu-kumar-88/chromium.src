// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_AUTOFILL_XML_PARSER_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_AUTOFILL_XML_PARSER_H_

#include <string>
#include <vector>

#include "components/autofill/core/browser/form_structure.h"

namespace autofill {

struct AutofillServerFieldInfo;

// The XML parser for parsing Autofill query responses.  A typical response
// looks like:
//
// <autofillqueryresponse uploadrequired="true">
//   <field autofilltype="0" />
//   <field autofilltype="1" />
//   <field autofilltype="3" />
//   <field autofilltype="2" />
//   <field autofilltype="61" defaultvalue="default" />
// </autofillqueryresponse>
//
// Fields are returned in the same order they were sent to the server.
// autofilltype: The server's guess at what type of field this is.  0
// is unknown, other types are documented in
// components/autofill/core/browser/field_types.h.
//
// Parses |xml| and on success returns true and fills |field_infos| based on the
// <field> tags and |upload_required| based on the uploadrequired attribute of
// the autofillqueryresponse tag. On failure returns false.
bool ParseAutofillQueryXml(std::string xml,
                           std::vector<AutofillServerFieldInfo>* field_infos,
                           UploadRequired* upload_required);

}  // namespace autofill

#endif  // COMPONENTS_AUTOFILL_CORE_BROWSER_AUTOFILL_XML_PARSER_H_
