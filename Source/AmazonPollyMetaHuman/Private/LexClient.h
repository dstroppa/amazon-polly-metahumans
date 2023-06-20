/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: MIT-0
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aws/core/Aws.h>
#include <aws/lexv2-runtime/model/RecognizeTextRequest.h>
#include <aws/lexv2-runtime/LexRuntimeV2Client.h>

/**
* Struct containing Lex data, to be used in PostText 
* NOTE: This struct was created to encapsulate all of the details 
* of the Lex SDK into this class. 
*/
struct LexOutcome {
    bool IsSuccess;
    Aws::String LexOutputMsg;
    Aws::String LexErrorMsg; 
};

/**
* Wrapper for LexClient that calls on Lex API, encapsulates AWS Lex SDK  
*/
class LexClient {

private:
    /**
    * LexClient used to invoke the Lex API (PostText)
    */
    TUniquePtr<Aws::LexRuntimeV2::LexRuntimeV2Client> AwsLexClient;

public:
    /*
    * Creates the LexClient
    */
    LexClient();

    virtual ~LexClient();
    /**
    * Calls on Lex SDK and returns a LexOutcome struct object with Lex data 
    * @param TextRequest - a configured TextRequest
    * @return LexOutcome - the struct containing the LexData
    */
    virtual LexOutcome RecognizeText(const Aws::LexRuntimeV2::Model::RecognizeTextRequest& TextRequest);
};