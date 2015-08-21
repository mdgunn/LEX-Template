--[[
Purpose: Simple counter script.
--]]

Script.Amount=0
Script.Max=2 -- int "Max Value"
Script.ModValue=1 -- int "Mod Value"

function Script:Start()
	WidgetSprite:Create(self.entity)
	self.savedvalue = self.Amount
end

function Script:AddValue()--in
	self.Amount=self.Amount+self.ModValue
	self:TestValue()
end

function Script:SubtractValue()--in
	self.Amount=self.Amount-self.ModValue
	self:TestValue()
end

function Script:MultiplyValue()--in
	self.Amount=self.Amount*self.ModValue
	self:TestValue()
end

function Script:DivideValue()--in
	self.Amount=self.Amount/self.ModValue
	self:TestValue()
end

function Script:TestValue()
	if self.savedvalue ~= self.Amount then
	
		if self.Amount > self.Max then
			self.Amount = self.Max
		end
		
		if self.Amount == self.Max then
			self.component:CallOutputs("OnHitMax")
			self.fired=true
		elseif self.fired then
			self.component:CallOutputs("OnLostMax")
			self.fired = false
		end
		
		self.savedvalue = self.Amount
	end
end