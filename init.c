void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	//Weather weather = g_Game.GetWeather();
	//weather.MissionWeather(false);    // false = use weather controller from Weather.c
	//weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	//weather.GetRain().Set( 0, 0, 1);
	//weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
	
    //CEApi TestHive = GetCEApi();
    //TestHive.ExportProxyProto();
    //TestHive.ExportProxyData( "8096 0 8096", 16384 );
    //TestHive.ExportClusterData() ;	  	
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );

		string steamID = player.GetIdentity().GetPlainId();
        // SET UP VIP STEAM ID
		array<string> targetSteamIDs = {"steamID"};
        // SET UP VIP LOADOUT
		array<string> extraItems = {"extraItems"};

		if (targetSteamIDs.Find(steamID) >= 0)
		{
			player.RemoveAllItems();

			for (int i = 0; i < extraItems.Count(); i++)
			{
				itemEnt = player.GetInventory().CreateInInventory(extraItems[i]);
			}
		}
		else
		{
			player.RemoveAllItems();
            // SET UP NON VIP LOADOUT
            itemEnt = player.GetInventory().CreateInInventory("DP_NewSpawn_BaseballCap");  
            itemEnt = player.GetInventory().CreateInInventory("DP_NewSpawn_Tshirt");
            itemEnt = player.GetInventory().CreateInInventory("DP_NewSpawn_CargoPants");
			itemEnt = player.GetInventory().CreateInInventory("DP_NewSpawn_pouches");			
            itemEnt = player.GetInventory().CreateInInventory("DP_NewSpawn_JungleBoots");   	
			itemEnt = player.GetInventory().CreateInInventory("DP_NewSpawn_TacticalGloves");
            itemEnt = player.GetInventory().CreateInInventory("DP_NewSpawn_PlateCarrierVest");
			itemEnt = player.GetInventory().CreateInInventory("FNX45");
            itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			itemEnt = player.GetInventory().CreateInInventory("WaterBottle");
			itemEnt = player.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
			itemEnt = player.GetInventory().CreateInInventory("PistolSuppressor");
			itemEnt = player.GetInventory().CreateInInventory("FNP45_MRDSOptic");
			itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan");
			itemEnt = player.GetInventory().CreateInInventory("PeachesCan");
			itemEnt = player.GetInventory().CreateInInventory("HeadTorch_Black");
			itemEnt = player.GetInventory().CreateInInventory("DP_Bandage");
			itemEnt = player.GetInventory().CreateInInventory("DP_HuntingKnife");
			itemEnt = player.GetInventory().CreateInInventory("DP_9v");
			itemEnt = player.GetInventory().CreateInInventory("DP_9v");
		}	
	}

	override void UpdatePlayersStats()
	{
		super.UpdatePlayersStats();
	
		array<Man> players = {};
		GetGame().GetPlayers(players);
	
		for (int i = 0; i < players.Count(); i++)
		{
			PlayerBase player;
			if (!PlayerBase.CastTo(player, players.Get(i)))
				continue;
	
			// update player's dogtag base on time
			float playtime = player.StatGet("playtime");
	
			if (playtime >= 3600 && playtime < 21600)
			{
				player.ReplaceDogtag("Dogtag_Silver");
			}
			else if (playtime >= 21600 && playtime < 43200)
			{
				player.ReplaceDogtag("Dogtag_Cobalt");
			}
			else if (playtime >= 43200 && playtime < 86400)
			{
				player.ReplaceDogtag("Dogtag_Granite");
			}
			else if (playtime >= 86400)
			{
				player.ReplaceDogtag("Dogtag_Hero");
			}
		}
	}
}

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}