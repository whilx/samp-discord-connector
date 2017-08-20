#pragma once

#include "CSingleton.hpp"
#include "types.hpp"
#include "sdk.hpp"

#include <string>
#include <memory>
#include <atomic>

#include <json.hpp>

#undef SendMessage // Windows at its finest


using json = nlohmann::json;


using User_t = std::unique_ptr<class User>;
using UserId_t = cell;

class User
{
public:
	User(UserId_t pawn_id, json &data);
	~User() = default;

private:
	const UserId_t m_PawnId;

	Snowflake_t m_Id;

	std::string
		m_Username,
		m_Discriminator,
		m_Email;

	bool
		m_IsBot = false,
		m_IsVerified = false;

public:
	inline UserId_t GetPawnId() const
	{
		return m_PawnId;
	}
	inline Snowflake_t const &GetId() const
	{
		return m_Id;
	}
	inline std::string const &GetUsername() const
	{
		return m_Username;
	}
	inline std::string const &GetDiscriminator() const
	{
		return m_Discriminator;
	}
	inline std::string const &GetEmail() const
	{
		return m_Email;
	}
	inline bool IsBot() const
	{
		return m_IsBot;
	}
	inline bool IsVerified() const
	{
		return m_IsVerified;
	}

};


class UserManager : public CSingleton<UserManager>
{
	friend class CSingleton<UserManager>;
private:
	UserManager() = default;
	~UserManager() = default;

private:
	const unsigned int m_InitValue = 2;
	std::atomic<unsigned int> m_Initialized{ 0 };

	std::map<unsigned int, User_t> m_Users; //PAWN channel-id to actual channel map

private:
	void AddUser(json &data);

public:
	void Initialize();
	void WaitForInitialization();

	User_t const &FindUser(UserId_t id);
	User_t const &FindUserByName(std::string const &name, std::string const &discriminator);
	User_t const &FindUserById(Snowflake_t const &sfid);
};