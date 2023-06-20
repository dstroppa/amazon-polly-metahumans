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

#include "LexClient.h" 
#include <aws/lexv2-runtime/model/RecognizeTextResult.h>
#include <aws/core/utils/Outcome.h>
#include <iostream>

LexClient::LexClient() {
    Aws::Client::ClientConfiguration configuration;
    configuration.userAgent = "request-source/AmazonPollyMetaHuman";
    AwsLexClient = MakeUnique<Aws::LexRuntimeV2::LexRuntimeV2Client>(configuration);
}

LexClient::~LexClient() {};

LexOutcome LexClient::RecognizeText(const Aws::LexRuntimeV2::Model::RecognizeTextRequest& TextRequest) {
    LexOutcome Outcome;
    Aws::LexRuntimeV2::Model::RecognizeTextOutcome TextOutcome = AwsLexClient->RecognizeText(TextRequest);
    if (TextOutcome.IsSuccess()) {
        if ((std::size(TextOutcome.GetResult().GetMessages()) == 0) || (TextOutcome.GetResult().GetMessages()[0].GetContent() == "")) {
            Outcome.LexOutputMsg = "Hello, welcome to the AWS Retail Demo Store Customer Service. I'm Ettore, and I'm here to help you. What can I do for you today?";
        }
        else {
            Outcome.LexOutputMsg = TextOutcome.GetResult().GetMessages()[0].GetContent();
        }
        Outcome.IsSuccess = true;
    }
    else {
        Outcome.IsSuccess = false;
        Outcome.LexErrorMsg = TextOutcome.GetError().GetMessage();
    }
    return Outcome;
}