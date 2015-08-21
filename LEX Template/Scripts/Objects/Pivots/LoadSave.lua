--[[
Purpose: A script to access the applications basic save and loading feature.
It should be noted that all what goes on is that on SaveFile(), the world
writes what map file the user is currently on. And LoadFile() function just reads
the .dat file and tells the world to load what map is written in it.

You should expand on this more to get information from other entitys like health, 
ammo, etc if I don't ever. Right now, a simple "What map was I playing last?" saving
feature is better than none at all!
--]]

function Script:Save()--in
	-- Don't run on Sandbox because there is no such thing as the app class!
	if SANDBOX then return end

	if (app:SaveFile()) then
		self.component:CallOutputs("Save")
	end
end

function Script:LoadFile()--in
	-- Don't run on Sandbox because there is no such thing as the app class!
	if SANDBOX then return end
	app:LoadSaveFile()
end