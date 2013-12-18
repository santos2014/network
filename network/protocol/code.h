#pragma once

namespace Santos
{
	enum Code
	{
		/// <summary>
		/// code begin , code define must be In what the following
		/// </summary>
		eBegin,

		/// <summary>
		/// error report
		/// </summary>
		ErrorReport,

		/// <summary>
		/// connect
		/// </summary>
		eNetwork,

		/// <summary>
		/// login
		/// </summary>
		eLogin,

		/// <summary>
		/// Register
		/// </summary>
		eRegister,

		/// <summary>
		/// GameLevel or GameSence
		/// </summary>
		eStage,

		/// <summary>
		/// Package
		/// </summary>
		ePackage,

		/// <summary>
		/// Hero Properties
		/// </summary>
		eHero,

		/// <summary>
		/// Friends
		/// </summary>
		eFriends,

		/// <summary>
		/// Help
		/// </summary>
		eHelp,

		/// <summary>
		/// offer a reward task
		/// </summary>
		eOfferReawardTask,

		/// <summary>
		/// Escort
		/// </summary>
		eEscort,

		/// <summary>
		/// Achievements
		/// </summary>
		eAchievements,

		/// <summary>
		/// Store
		/// </summary>
		eStore,

		/// <summary>
		/// WorldBoss
		/// </summary>
		eWorldBoss,

		/// <summary>
		/// rank
		/// </summary>
		eRank,

		/// <summary>
		/// DailyActive
		/// </summary>
		eDailyActive,

		/// <summary>
		/// mail
		/// </summary>
		eMail,

		/// <summary>
		/// sign
		/// </summary>
		eSign,

		/// <summary>
		/// vip
		/// </summary>
		eVip,

		eEnd,
	};

	enum Sumcode_login{
		/// <summary>
		/// 创建角色成功
		/// </summary>
		SyncCreateRole,

		/// <summary>
		/// 请求创建角色
		/// </summary>
		RequireToCreateRole,

		/// <summary>
		/// 身份验证
		/// </summary>
		LogIn,
	};
}