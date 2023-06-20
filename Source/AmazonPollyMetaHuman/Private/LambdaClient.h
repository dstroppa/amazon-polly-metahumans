#pragma once


#include <aws/core/Aws.h>
#include <aws/lambda/model/InvokeRequest.h>
#include <aws/lambda/LambdaClient.h>

/**
* Struct containing Lambda invocation outcome, to be used in Invoke
* NOTE: This struct was created to encapsulate all of the details
* of the Lambda SDK into this class.
*/
struct LambdaOutcome {
    bool IsSuccess;
    Aws::String LambdaOutputMsg;
    Aws::String LambdaErrorMsg;
};

/**
* Wrapper for LambdaClient that calls on Lambda API, encapsulates AWS Lambda SDK
*/
class LambdaClient {

private:
    /**
    * LambdaClient used to invoke the Lambda API (Invoke)
    */
    TUniquePtr<Aws::Lambda::LambdaClient> AwsLambdaClient;

public:
    /*
    * Creates the LambdaClient
    */
    LambdaClient();

    virtual ~LambdaClient();
    /**
    * Calls on Lambda SDK and returns a LambdaOutcome struct object with Lambda data
    * @param InvokeRequest - a configured InvokeRequest
    * @return LambdaOutcome - the struct containing the LambdaData
    */
    virtual LambdaOutcome Invoke(const Aws::Lambda::Model::InvokeRequest& InvokeRequest);
};
