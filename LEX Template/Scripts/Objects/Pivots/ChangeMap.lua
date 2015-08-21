--[[
Purpose:  Tell the app to change the map.
--]]

Script.enabled=true--bool "Start Enabled"
Script.mapname=""--string "Map Name"

function Script:Start()
	WidgetSprite:Create(self.entity)
end

function Script:ChangeMap()--in
	if not SANDBOX then
		if self.enabled then
			app:LoadMap(self.mapname)
		end
	else
		LoadMap(self.mapname)
	end
end