--Finite state machine base class
if( FSM_Base == nil ) then
	FSM_Base = class( nil, {} );

	FSM_Base.Update = function( self, frameTime )
		print( "ERROR: FSM_Base:Update not implemented." );
	end

	FSM_Base.ChangeState = function( self )
		print( "ERROR: FSM_Base:ChangeState not implemented." );
	end
end

--Fight
if( FSM_Fight == nil ) then
	FSM_Fight = class( FSM_Base, {} );

	FSM_Fight.Update = function( self, frameTime )
		health = GetGOVariable( "test", "int" );
		if( health ~= nil ) then
			health = health - 3;
			print( "[Lua_Brain] Hit" );
			SetGOVariable( "test", health, "int" );
		end
	end

	FSM_Fight.ChangeState = function( self )
		health = GetGOVariable( "test", "int" );
		if( health ~= nil and health < 2 ) then
			return StateTable[ "Heal" ];
		end
		return nil;
	end
end

--Heal
if( FSM_Heal == nil ) then
	FSM_Heal = class( FSM_Base, {} );

	FSM_Heal.Update = function( self, frameTime )
		testVarExt = GetGOExtVariable( 0, "test", "int" );
		health = GetGOVariable( "test", "int" );
		if( health ~= nil ) then
			health = health + 5;
			print( "[Lua_Brain] Heal / testVarExt = ", testVarExt );
			SetGOVariable( "test", health, "int" );
		end
	end

	FSM_Heal.ChangeState = function( self )
		health = GetGOVariable( "test", "int" );
		if( health ~= nil and health > 10 ) then
			return StateTable[ "Fight" ];
		end
		return nil;
	end
end

if( StateTable == nil ) then
	StateTable = {
		Fight = FSM_Fight:Create( {}, nil ),
		Heal = FSM_Heal:Create( {}, nil )
	};
end

--Agent brain
if( FSM_Brain == nil ) then
	FSM_Brain = class( nil, { currentState = nil } );

	FSM_Brain.Update = function( self, frameTime )
		if( currentState == nil ) then
			currentState = StateTable["Fight"];
		end;
		currentState:Update( frameTime );
		nextState = currentState:ChangeState();
		if( nextState ~= nil ) then
			currentState = nextState;
		end
	end
end
