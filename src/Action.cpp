#include "include/Action.h"

/***
 * BaseAction
 * */
BaseAction::BaseAction():status(PENDING),errorMsg("Error - ") {

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status=COMPLETED;
}

void BaseAction::error(const std::string &errorMsg) {
    status=ERROR;
    std::cout << errorMsg << std::endl;

}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

/***
 *crate user
 * */


void CreateUser::act(Session &sess) {


}

std::string CreateUser::toString() const {
    return std::string();
}


