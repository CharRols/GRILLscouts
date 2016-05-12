using UnityEngine;
using System.Collections;

public class StudentNetworkManager : InstructorNetworkManager {
	
	private const string typeName = "SinclairNetworkTest";
	private const string gameName = "Begin";
	private const int maxPlayers = 50; //the maximum number of players allowed on the server
	private bool showMessage = false;
	private string sMessage;
	private HostData[] hostList;
	public Transform playerPrefab;
	public Object play;

	// Use this for initialization
	void Start () {}//end Start
	
	private void RefreshHostList(){
		MasterServer.RequestHostList(typeName);
	}//end RefreshHostList
	
	void OnMasterServerEvent(MasterServerEvent msEvent){
		if (msEvent == MasterServerEvent.HostListReceived) {
			hostList = MasterServer.PollHostList ();
		}//end if
	}//end onMasterServerEvent
	
	private void JoinServer(HostData hostData){
		Network.Connect(hostData);
	}//end JoinServer
	
	void OnConnectedToServer(){
		Debug.Log("Server Joined");
		sMessage = "Server Joined";
		showMessage = true;
		this.Invoke ("stopMessage", 5);
		Network.SetReceivingEnabled (Network.connections [0], 0, true);
		Debug.Log(gameObject.GetComponent<NetworkView>().viewID);
	}//end onConnectedToServer
	
	private void SpawnPlayer(){
		play = Network.Instantiate(playerPrefab, new Vector3(0f, 5f, 0f), Quaternion.identity, 0);
	}//end spawnplayer
	
	[RPC]
	void displayMessage(string someinfo){//doesn't work yet
		sMessage = someinfo;
		showMessage = true;
		this.Invoke ("stopMessage", 5);//displays message for 5 seconds
	}//end display message
	
	void stopMessage(){
		showMessage = false;
	}//end stopMessage

	void messageInstructor(){
		string help = "I Need Help!";
		Network.SetSendingEnabled (0, true);
		gameObject.AddComponent<InstructorNetworkManager> ();
		Debug.Log (gameObject.GetComponent<InstructorNetworkManager>());
		gameObject.GetComponent<NetworkView>().RPC ("displayStudentMessage", RPCMode.Others, help);
	}//end messageInstructor
	
	void OnGUI()
	{
		if (showMessage) {
			GUI.Label(new Rect(10f, 10f, 100f, 50f), sMessage);
		}//end if
		if (!Network.isClient && !Network.isServer){
			
			if (GUI.Button(new Rect(100, 100, 250, 100), "Refresh Hosts"))
				RefreshHostList();
			
			if (hostList != null){
				for (int i = 0; i < hostList.Length; i++)
				{
					if (GUI.Button(new Rect(400, 100 + (110 * i), 250, 100), hostList[i].gameName))
						JoinServer(hostList[i]);
				}//end for
			}//end inner (hostList != null) if
		}//end outer (!Network.isClient && !Network.isServer) if
		if (Network.isClient) {
			if(GUI.Button( new Rect(100, 100, 250, 100), "Ask for help")){
				messageInstructor();
			}//end inner if
		}//end outer if
	}//end onGUI
	
	// Update is called once per frame
	void Update () {}//end update
}//end class