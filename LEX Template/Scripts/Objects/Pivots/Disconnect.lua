--[[
Purpose: Tell the app to disconnect the client.
--]]

Script.enabled=true--bool "Start Enabled"
Script.killapp=false--bool "Quit Instead"

function Script:Start()
	WidgetSprite:Create(self.entity)
end


function Script:Disconnect()--in
	if self.enabled then
		if not SANDBOX then
			if not self.killapp then
				app:Disconnect()
			else
				app:Quit()
			end
		else
			-- All we can do is stop it from looping.
			SHUTDOWN = true
		end
	end
end