if( BasicBrain == nil ) then

	BasicBrain = class( nil, {cooldown = 3, coolState = 0} );

	BasicBrain.Update = function( self, frameTime )
		self.coolState = self.coolState + frameTime;
		if( self.coolState >= self.cooldown ) then
			testVariable = GetGOVariable( "test", "int" );
			if( testVariable ~= nil ) then
				SetGOVariable( "test", testVariable - 1, "int" );
			end
			self.coolState = 0;
		end
	end

end
