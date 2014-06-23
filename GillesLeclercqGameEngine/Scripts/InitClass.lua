--Class abstraction
function class( baseClass, body )
	local result = body or {};
	
	--Set up the inheritance hierarchy if needed
	if( baseClass ~= nil ) then
		setmetatable( result, result );
		result.__index = baseClass;
	end
	
	--Used to instantiate a object of this class
	function result.Create( self, constructionData, originalSubClass )
		local obj;
		--Recursively create the inheritance chain
		if( self.__index ~= nil ) then
			if( originalSubClass ~= nil ) then
				obj = self.__index:Create( constructionData, originalSubClass );
			else
				obj = self.__index:Create( constructionData, self );
			end
		else
			obj = constructionData or {};
		end
		
		setmetatable( obj, obj );
		obj.__index = self;
		
		if( self.__operators ~= nil ) then
			for key, val in pairs( self.__operators ) do
				obj[key] = val;
				print( key );
			end
		end
		
		return obj;
	end
	
	return result;
end