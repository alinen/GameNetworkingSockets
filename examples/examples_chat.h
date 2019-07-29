#include <string>


class examples_chat {
  public:
    static void NukeProcess(int rc);
    static void DebugOutput(ESteamNetworkingSocketsDebugOutputType eType, const char *pszMsg);
    static void FatalError(const char *fmt, ...);
    static void Prinf(const char *fmt, ...);
    static void InitSteamDatagramConnectionSockets();
    static void ShutdownSteamDatagramConnectionSockets();
    void LocalUserInput_Init();
    void LocalUserInput_Kill();
    static inline void ltrim(std::string &s);
    static inline void rtrim(std::string &s);
    bool LocalUserInput_GetNext(std::string &result);
    void PrintUsageAndExit( int rc = 1 );

    class ChatServer : private ISteamNetworkingSocketsCallbacks
    {
     public:
       Run(uint16 nPort);
     private:
       void SendStringToClient(HSteamNetConnection conn, const char *str);
       void SendStringToAllClients(const char *str, HSteamNetConnection except = k_HSteamNetConnection_Invalid);
       void PollIncomingMessages();
       void PollLocalUserInput();
       void SetClientNick(HSteamNetConnection hConn, const char *nick );
       virtual void OnSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo ) override;
    }

    class ChatClient : private ISteamNetworkingSocketsCallbacks
    {
     public:
       void Run(const SteamNetworkingIPAddr &serverAddr);
     private:
       void PollIncomingMessages();
       void PollConnectionStateChanges();
       void PollLocalUserInput();
	     virtual void OnSteamNetConnectionStatusChanged( SteamNetConnectionStatusChangedCallback_t *pInfo ) override;
}



}
