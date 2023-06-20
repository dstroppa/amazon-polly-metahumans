#include "LambdaClient.h" 
#include <aws/lambda/model/InvokeResult.h>
#include <aws/core/utils/Outcome.h>
#include <iostream>
#include <aws/lambda/LambdaRequest.h>


LambdaClient::LambdaClient() {

    Aws::Client::ClientConfiguration configuration;
    configuration.userAgent = "request-source/AmazonPollyMetaHuman";

    AwsLambdaClient = MakeUnique<Aws::Lambda::LambdaClient>(configuration);

}

LambdaClient::~LambdaClient() {};

LambdaOutcome LambdaClient::Invoke(const Aws::Lambda::Model::InvokeRequest& InvokeRequest) {
    LambdaOutcome Outcome;
    Aws::Lambda::Model::InvokeOutcome invokeResult;

    auto outcome = AwsLambdaClient->Invoke(InvokeRequest);

    if (outcome.IsSuccess()) {
        invokeResult = std::move(outcome.GetResult());

        auto json_response = Aws::Utils::Json::JsonValue(invokeResult.GetResult().GetPayload());
        if (!json_response.WasParseSuccessful()) {
            // handle error, maybe set Outcome.IsSuccess = false and return
        }

        Aws::String functionResult = json_response.View().WriteCompact();

        if (functionResult.empty()) {
            Outcome.LambdaOutputMsg = "Hello, the lambda function returned no specific message.";
        }
        else {
            Outcome.LambdaOutputMsg = functionResult;  // no need for conversion
        }

        Outcome.IsSuccess = true;
    }
    else {
        Outcome.IsSuccess = false;
        Outcome.LambdaErrorMsg = outcome.GetError().GetMessage();
    }

    return Outcome;
}

