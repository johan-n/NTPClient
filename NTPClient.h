#pragma once

#include "Arduino.h"

#include <Udp.h>

#define SEVENZYYEARS 2208988800UL
#define NTP_PACKET_SIZE 48
#define NTP_DEFAULT_LOCAL_PORT 1337
#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ) )


class NTPClient {
  private:
    UDP*          _udp;
    bool          _udpSetup       = false;

    const char*   _poolServerName = "pool.ntp.org"; // Default time server
    int           _port           = NTP_DEFAULT_LOCAL_PORT;
    int           _timeOffset     = 0;

    unsigned long _updateInterval = 60000;  // In ms

    unsigned long _currentEpoc    = 0;      // In s
    unsigned long _lastUpdate     = 0;      // In ms

    byte          _packetBuffer[NTP_PACKET_SIZE];

    void          sendNTPPacket();
    bool          isValid(byte * ntpPacket);

  public:
    NTPClient(UDP& udp);
    NTPClient(UDP& udp, int timeOffset);
    NTPClient(UDP& udp, const char* poolServerName);
    NTPClient(UDP& udp, const char* poolServerName, int timeOffset);
    NTPClient(UDP& udp, const char* poolServerName, int timeOffset, unsigned long updateInterval);

    /**
     * Starts the underlying UDP client with the default local port
     */
    void begin();

    /**
     * Starts the underlying UDP client with the specified local port
     */
    void begin(int port);

    /**
     * This should be called in the main loop of your application. By default an update from the NTP Server is only
     * made every 60 seconds. This can be configured in the NTPClient constructor.
     *
     * @return true on success, false on failure
     */
    bool update();

    /**
     * This will force the update from the NTP Server.
     *
     * @return true on success, false on failure
     */
    bool forceUpdate();

    /**
     * Changes the time offset. Useful for changing timezones dynamically
     */
    void setTimeOffset(int timeOffset);

    /**
     * Changes the time offset. Useful for changing timezones dynamically
     */
    void setDTS(bool dts);

    /**
     * @return time in seconds since Jan. 1, 1970
     */
    unsigned long getEpochTime();

    /**
     * @return days since Jan. 1, 1970
     */
    unsigned long getEpochDays();

    /**
     * @return Year
     */
    int getYear();

    /**
     * @return number of the Month
     * January = 1
     */
    int getMonth();
            
    /**
     * @return Day Of The Year
     */
    int getDayOTY();
    
    /**
     * @return Day Of The Month
     */
    int getDayOTM();
    
    /**
     * @return Day Of The Week
     * Sunday = 0
     */
    int getDayOTW();

    /**
     * @return Hour of the day
     */
    int getHours();

    /**
     * @return Minutes of hour
     */
    int getMinutes();

    /**
     * @return seconds of the minute
     */
    int getSeconds();
    
    /**
     * Set the update interval to another frequency. E.g. useful when the
     * timeOffset should not be set in the constructor
     */
    void setUpdateInterval(unsigned long updateInterval);

    /**
    * @return secs argument (or 0 for current time) formatted like `hh:mm:ss`
    */
    String getFormattedTime(unsigned long secs = 0);

    /**
    * @return dae formatted like 'YYYY-MM-DD' (ISO 8601)
    * like `2004-02-14`
    */
    String getFormattedDateYMD();

    /**
    * @return dae formatted like 'MM/DD/YYYY'
    * like `02/14/2004`
    */
    String getFormattedDateMDY();

    /**
    * @return dae formatted like 'YYYY-MM-DD' (ISO 8601)
    * like `14/02/2004`
    */
    String getFormattedDateDMY();
    

     /**
     * @return time formatted like `DD:MM:YYYY hh:mm:ss`
     */
    String getFullFormattedTime(); 


    /**
     * Stops the underlying UDP client
     */
    void end();

    /**
    * Replace the NTP-fetched time with seconds since Jan. 1, 1970
    */
    void setEpochTime(unsigned long secs);
};
