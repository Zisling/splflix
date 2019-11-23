#include "include/Action.h"
#include "include/User.h"
#include "include/Session.h"

/***
 * BaseAction
 * */
BaseAction::BaseAction():status(PENDING),errorMsg("") {

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status=COMPLETED;
}

void BaseAction::error(const std::string &errorMsg) {
    status=ERROR;
    this->errorMsg.append(errorMsg);
    std::cout << this->errorMsg << std::endl;

}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

BaseAction::BaseAction(const BaseAction &other):status(other.status),errorMsg(other.errorMsg) {}

BaseAction &BaseAction::operator=(const BaseAction &other) {
    status=other.status;
    errorMsg=other.errorMsg;
    return *this;
}

BaseAction::BaseAction(BaseAction &&other):status(other.status),errorMsg(std::move(other.errorMsg)) {
    other.status=PENDING;
}

BaseAction &BaseAction::operator=(BaseAction &&other) {
    status=other.status;
    other.status=PENDING;
    errorMsg=std::move(errorMsg);
    return *this;
}


BaseAction::~BaseAction() = default;

/***
 *crate user
 ***/


void CreateUser::act(Session &sess) {
    std::string name;
    std::string Type;
    std::cin>>name;
    std::cin>>Type;
    if (sess.getUserMap().find(name)==sess.getUserMap().end()){
        if (Type=="len") {
            User *toSend = new LengthRecommenderUser(name);
            sess.insertNewUser(toSend, name);
            complete();
        }
        else if (Type=="rer") {
            User *toSend = new RerunRecommenderUser(name);
            sess.insertNewUser(toSend, name);
            complete();
        }
        else if (Type=="gen") {
            User *toSend = new GenreRecommenderUser(name);
            sess.insertNewUser(toSend, name);
            complete();
        } else{error("Error - non exiting type");}
    } else{
        error("Error - user all ready exist");
    }
}

std::string CreateUser::toString() const {
    std::string statusSt;
    if (getStatus()==PENDING){statusSt="PENDING";}
    if (getStatus()==COMPLETED){statusSt="COMPLETED";}
    if (getStatus()==ERROR){statusSt="ERROR";
    return "create user "+statusSt+" "+getErrorMsg();}
    return "create user "+statusSt;
}
/***
 * ChangeActiveUser
 ***/

void ChangeActiveUser::act(Session &sess) {
    std::string name;
    std::cin>>name;
    if(sess.getUserMap().find(name)!=sess.getUserMap().end()){
        sess.chaneActiveUser(name);
        complete();
    } else{
        error("Error - user don't exist");
    }
}

std::string ChangeActiveUser::toString() const {
    std::string statusSt;
    if (getStatus()==PENDING){statusSt="PENDING";}
    if (getStatus()==COMPLETED){statusSt="COMPLETED";}
    if (getStatus()==ERROR){statusSt="ERROR";
        return "change user "+statusSt+" "+getErrorMsg();}
    return "change user "+statusSt;
}
/**
 *deleteuser
 **/

void DeleteUser::act(Session &sess) {
    std::string name;
    std::cin>>name;
    if(sess.getUserMap().find(name)!=sess.getUserMap().end()){
        if (sess.getActiveUser()== nullptr || sess.getActiveUser()->getName()!=name){
        sess.deleteUser(name);
        complete();}
        else{error("Error - active user can't be deleted please change active user");}
    } else{
        error("Error - user don't exist");
    }
}

std::string DeleteUser::toString() const {
    std::string statusSt;
    if (getStatus()==PENDING){statusSt="PENDING";}
    if (getStatus()==COMPLETED){statusSt="COMPLETED";}
    if (getStatus()==ERROR){statusSt="ERROR";
        return "delete user "+statusSt+" "+getErrorMsg();}
    return "delete user "+statusSt;
}
/**
 * duplicateUser
 * */
void DuplicateUser::act(Session &sess) {
//TODO: need to make it after User copy constructor is made
}

std::string DuplicateUser::toString() const {
    std::string statusSt;
    if (getStatus()==PENDING){statusSt="PENDING";}
    if (getStatus()==COMPLETED){statusSt="COMPLETED";}
    if (getStatus()==ERROR){statusSt="ERROR";
        return "duplicate user "+statusSt+" "+getErrorMsg();}
    return "duplicate user "+statusSt;
}

/***
 * PrintContentList
 ***/
void PrintContentList::act(Session &sess) {
    if (!sess.getContent().empty()){
        for (const auto &content : sess.getContent()) {
            std::string tagsSt;
            if(!content->getTags().empty()){
                tagsSt=" [";
                for (auto iterator = content->getTags().begin(); iterator != content->getTags().end()-1; ++iterator) {
                    tagsSt.append(*iterator.base()+", ");
                }
                tagsSt.append(content->getTags().at(content->getTags().size()-1) + "]");
            }
            std::cout<<content->getId() <<". " <<content->toString() <<" "<<content->getLength()<<" minutes"<<tagsSt << std::endl;
        }
        complete();
    } else{
        error("no content available");
    }
}

std::string PrintContentList::toString() const {
    std::string statusSt;
    if (getStatus()==PENDING){statusSt="PENDING";}
    if (getStatus()==COMPLETED){statusSt="COMPLETED";}
    if (getStatus()==ERROR){statusSt="ERROR";
        return "content "+statusSt+" "+getErrorMsg();}
    return "content "+statusSt;
}
/***
 * PrintWathchHistory
 ***/
void PrintWatchHistory::act(Session &sess) {
    sess.getActiveUser()->PrintHistory();
    complete();
}

std::string PrintWatchHistory::toString() const {
    return std::string();
}


/***
 * watch
 * */
void Watch::act(Session &sess) {
    int id;
    std::cin>>id;
    watchById(id,sess);
    }



std::string Watch::toString() const {
    std::string statusSt;
    if (getStatus()==PENDING){statusSt="PENDING";}
    if (getStatus()==COMPLETED){statusSt="COMPLETED";}
    if (getStatus()==ERROR){statusSt="ERROR";
        return "Watch "+statusSt+" "+getErrorMsg();}
    return "Watch "+statusSt;
}

void Watch::watchById(int id,Session &sess) {
    if(id>0 && id<sess.getContent().size()+1){
        Watchable* toInsert =sess.getContent()[id-1];
        sess.getActiveUser()->insertToHistory(toInsert);
        std::cout <<"Watching "<<toInsert->toString() << std::endl;
            Watchable* recommend = sess.getActiveUser()->getRecommendation(sess);
            std::cout << "We recommend watching " << recommend->toString() << ",continue watching? [y/n] " << std::endl;
            std::cout<<recommend->getId()<<std::endl;
            std::string userCommand;
            std::cin>>userCommand;
        while (userCommand!="n"){
            if (userCommand=="y"){
                watchById(recommend->getId(),sess);
                userCommand="n";}
            else if(userCommand!= "n"){
                std::cout << "[y/n] input"<< std::endl;
                std::cin>>userCommand;
            }
        }
        complete();

    } else{
        error("this id don't exist");
    }
}

void PrintActionsLog::act(Session &sess) {


}

std::string PrintActionsLog::toString() const {
    std::string statusSt;
    if (getStatus()==PENDING){statusSt="PENDING";}
    if (getStatus()==COMPLETED){statusSt="COMPLETED";}
    if (getStatus()==ERROR){statusSt="ERROR";
        return "PrintActionLog "+statusSt+" "+getErrorMsg();}
    return "PrintActionLog "+statusSt;
}


