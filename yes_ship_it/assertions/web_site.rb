module YSI
  class WebSite < Assertion
    def self.display_name
      "Web site up to date"
    end

    def check
      html = RestClient.get("http://cornelius-schumacher.de/polka")
      if html =~ /Polka #{engine.version}/
        engine.version
      else
        nil
      end
    end

    def assert(executor)
      engine.out.puts "..."
      engine.out.puts "  Can't update the web page automatically."
      engine.out.puts "  Please update the web page with version #{engine.version}"
      "... #{engine.version}"
    end
  end
end
