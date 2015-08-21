--[[
Purpose: A entity that plays a sound file.
--]]

Script.soundfile=""--path "File" "Waveform Audio File Format (*.wav):wav|Sound"
Script.playing=true--bool "Start Playing"
Script.enabled=true--bool "Enabled"

-- Vec2's are used for random values. 
-- Keep both x and y the same for a fixed value.
Script.volume=Vec2(100,100)--Vec2 "Volume"
Script.pitch=Vec2(1.0,1.0)--Vec2 "Pitch"
Script.range=Vec2(50,50)--Vec2 "Range"
Script.playeverywhere=false--bool "Play Everywhere"
Script.loop=false--bool "Loop"
Script.sourceentity="" --entity "Source Entity"

function Script:Start()
	WidgetSprite:Create(self.entity)
	self.source = Source:Create()

	-- Volume
	local vol = math.floor(Math:Random(self.volume.x, self.volume.y))
	self.source:SetVolume(vol/MAXVOLUME)
	
	-- Pitch
	local pit = math.floor(Math:Random(self.pitch.x, self.pitch.y))
	self.source:SetPitch(pit)
	
	-- Range
	local rag = math.floor(Math:Random(self.range.x, self.range.y))
	if self.playeverywhere then
		self.source:SetRange(999)
	else
		self.source:SetRange(rag)
	end
	
	self.source:SetLoopMode(self.loop)
	
	if self.sourceentity ~= "" then
		self.source:SetPosition(self.sourceentity:GetPosition(true))
	else
		self.source:SetPosition(self.entity:GetPosition(true))
	end
	
	local sound = Sound:Load(self.soundfile)
	if sound~=nil then
		self.source:SetSound(sound)
		if self.playing==true and self.enabled==true then
			self.source:Play()
		end
		sound:Release()
		sound=nil
	end
end

function Script:UpdateWorld()
	-- Always update the position of the sound if attached to an entity.
	if self.sourceentity ~= "" then
		self.source:SetPosition(self.sourceentity:GetPosition(true))
	end
end

function Script:Play()--in
	if self.enabled then
		self.source:Play()
	end
	self.component:CallOutputs("Play")
end

function Script:Pause()--in
	if self.enabled then
		self.source:Pause()
	end
	self.component:CallOutputs("Pause")
end

function Script:Resume()--in
	if self.enabled then
		self.source:Resume()
	end
	self.component:CallOutputs("Resume")
end

function Script:Stop()--in
	if self.enabled then
		self.source:Stop()
	end
	self.component:CallOutputs("Stop")
end

function Script:Enable()--in
	self.enabled=true
end

function Script:Disable()--in
	self.enabled=false
end

function Script:Release()
	if self.source then
		self.source:Release()
		self.source=nil
	end
end