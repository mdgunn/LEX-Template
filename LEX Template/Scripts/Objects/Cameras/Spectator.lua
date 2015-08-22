--[[
Purpose: A spectator camera that can go anywhere with WASD and mouse look.
]]--

Script.moveSpeed = 0.2 		--float "Move Speed"
Script.mouseDifference = Vec2(0,0)
Script.cameraMovement = Vec3(0,0,0)
Script.input={}

function Script:Start()

	local window = Window:GetCurrent()
	local context = Context:GetCurrent()
	
	self.camRotation = self.entity:GetRotation(true)
	self.listener = Listener:Create(self.entity)
		
	local window = Window:GetCurrent()
	local context = Context:GetCurrent()
	
	window:SetMousePosition(Math:Round(context:GetWidth()/2), Math:Round(context:GetHeight()/2))
	
	self.entity:SetRotation(self.camRotation)
end

function Script:UpdateWorld()
	local window = Window:GetCurrent()
	local context = Context:GetCurrent()

	-- Update these values.
	self.entity:SetMultisampleMode((System:GetProperty("multisample","1")))
	self.entity:SetFOV((System:GetProperty("fov","70")))
	self.mouseSensitivity = System:GetProperty("mousesensitivity","18")

	--Mouse look
	self.currentMousePos = window:GetMousePosition()
	window:SetMousePosition(Math:Round(context:GetWidth()/2), Math:Round(context:GetHeight()/2))
	self.currentMousePos.x = Math:Round(self.currentMousePos.x)
	self.currentMousePos.y = Math:Round(self.currentMousePos.y)	
	
	self.mouseDifference.x = Math:Curve(self.currentMousePos.x - Math:Round(context:GetWidth()/2),self.mouseDifference.x,3)
	self.mouseDifference.y = Math:Curve(self.currentMousePos.y - Math:Round(context:GetHeight()/2),self.mouseDifference.y,3)

	self.camRotation.x = Math:Clamp(self.camRotation.x + self.mouseDifference.y / self.mouseSensitivity,-90,90)
	self.camRotation.y = self.camRotation.y + (self.mouseDifference.x / self.mouseSensitivity)
	
	self.entity:SetRotation(self.camRotation)
	
end

--This function will be called once per physics update
function Script:UpdatePhysics()
	local window = Window:GetCurrent()
	local context = Context:GetCurrent()
	
--Player Movement
	local movex=0
	local movez=0
	self.input[0]=0
	self.input[1]=0
	if window:KeyDown(Key.W) then self.input[1]=self.input[1]+1 end
	if window:KeyDown(Key.S) then self.input[1]=self.input[1]-1 end
	if window:KeyDown(Key.D) then self.input[0]=self.input[0]+1 end
	if window:KeyDown(Key.A) then self.input[0]=self.input[0]-1 end
	
	local cameraMovement = Vec3(0)
	cameraMovement.x = self.input[0] * self.moveSpeed
	cameraMovement.z = self.input[1] * self.moveSpeed
	
	--This prevents "speed hack" strafing due to lazy programming
	if self.input[0]~=0 and self.input[1]~=0 then
		cameraMovement = cameraMovement * 0.70710678
	end
	
	self.entity:Move(cameraMovement.x,0,cameraMovement.z)
end