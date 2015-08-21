--[[
Purpose: A Point in 3D space that spawns the player. A player start in some cases is
better then placing the player as you might wish to respawn the player if they have
died. 
]]--

--Script.PlayerScript ="" --path "Player Script" "Script (*.lua):lua|Scripts"
Script.PlayerFile="" --path "Player" "Script (*.lua):lua:Prefab (*.pfb):pfb|Scripts" 
function Script:Start()
	WidgetSprite:Create(self.entity)
	
	local fileext = FileSystem:ExtractExt(self.PlayerFile)

	local player
	
	if fileext == "lua" then
		player = Pivot:Create()
		player:SetPosition(self.entity:GetPosition())
		player:SetRotation(self.entity:GetRotation())
		player:SetScript(self.PlayerFile)
		System:Print("Created Player via Script!")
	elseif fileext == "pfb" then
		player = Prefab:Load(self.SpawnObject)
		if player~=nil then
			player:SetPosition(self.entity:GetPosition())
			player:SetRotation(self.entity:GetRotation())
			System:Print("Created Player via Prefab!")
		end	
	else
		Debug:Error("Invaild Player") 
		return
	end
	
	if type(player.script.SetNewRespawnPoint)=="function" then
		player.script:SetNewRespawnPoint(self.entity)	
	end	
	
end