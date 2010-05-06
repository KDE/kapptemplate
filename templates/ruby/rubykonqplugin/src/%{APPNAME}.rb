#!/usr/bin/env ruby
require 'Qt'
require 'korundum4'
require 'khtml'
require 'kio'
require 'ui_config.rb'
require 'settings.rb'

include KDE
include Qt

module %{APPNAMEFU}

class %{APPNAMEFU}ConfigView < Widget
	slots :settingsChanged
	attr_reader :settings
	
	def initialize(parent)
		super(parent)
		@ui = Ui::ConfigDialog.new
		@ui.setupUi(self)
		# Note that the Settings class is a singleton
		@settings = Settings.instance
		settingsChanged()
		setAutoFillBackground(true)
	end
	
	def settingsChanged()
		
	end
end

class %{APPNAMEFU} < KParts::Plugin
	slots :helloWorld, :showConfig
	def initialize(parent, parentWidget, args)
		super(parent)
		puts "Ruby %{APPNAMEFU}"
		if !parent.is_a? HTMLPart
			qWarning("%{APPNAMEFU} Ruby Konqueror Plugin: Not a KHTML-Part")
			return
		end
		@part = parent
		@action = Qt::Action.new("Hello World", self)
		@configAction = actionCollection().addAction("configure_%{APPNAME}")
		connect(@configAction, SIGNAL('triggered()'), self, SLOT('showConfig()'))
		
		actionCollection().addAction("tools_%{APPNAME}", @action)
		connect(@action, SIGNAL('triggered()'), self, SLOT('helloWorld()'))
		@config = %{APPNAMEFU}ConfigView.new(parentWidget)
		@settings = Settings.instance
	end
	def helloWorld()
		Qt::MessageBox::information(nil, "Hello World!", "Greetings from Ruby");
	end
	def showConfig()
		if @dialog == nil
			@dialog = KDE::ConfigDialog.new(self, "plugin_%{APPNAMELC}_settings", @settings)
			@dialog.addPage(@config, KDE::i18n("%{APPNAME} General Settings"), "package_setting")
		end
		@dialog.show
	end
end

end
