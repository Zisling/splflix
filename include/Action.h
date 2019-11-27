#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

class Session;

enum ActionStatus{
	PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
	BaseAction();
	ActionStatus getStatus() const;
	virtual void act(Session& sess)=0;
	virtual std::string toString() const=0;

    virtual ~BaseAction();
    BaseAction(const BaseAction &other);
    BaseAction&operator=(const BaseAction& other);
    BaseAction(BaseAction && other);
    BaseAction&operator=(BaseAction&& other);
    virtual BaseAction* copy()=0;

protected:
	void complete();
	void error(const std::string& errorMsg);
	std::string getErrorMsg() const;
private:
	std::string errorMsg;
	ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};

class ChangeActiveUser : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};

class DeleteUser : public BaseAction {
public:
	virtual void act(Session & sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};


class DuplicateUser : public BaseAction {
public:
	virtual void act(Session & sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};

class PrintContentList : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};

class PrintWatchHistory : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};


class Watch : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
	void watchById(unsigned long id,Session &sess);

    BaseAction *copy() override;
};


class PrintActionsLog : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};

class Exit : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;

    BaseAction *copy() override;
};
#endif
