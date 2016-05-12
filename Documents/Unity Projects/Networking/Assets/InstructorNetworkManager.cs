using UnityEngine;
using System.Collections;

public class InstructorNetworkManager : MonoBehaviour {

	private const string typeName = "SinclairNetworkTest";
	private const string gameName = "Begin";
	const string someInfo = "Hello world";
	private const int maxPlayers = 50; //the maximum number of players allowed on the server
	private bool InstshowMessage = false;
	private string message;
	private HostData[] hostList;
	public Transform instPrefab;
	private ArrayList players;

	// Use this for initialization
	void Start () {}//end Start

	void OnPlayerConnected(NetworkPlayer student){ //automatically called when a player connects to the server.
		Debug.Log ("Player connected from: " + student.ipAddress);//displays message showing the ip address of the new player
		Network.SetReceivingEnabled (student, 0, true);
	}//end on playerConnected

	private void StartServer(){
		Network.InitializeServer(maxPlayers, 25000, !Network.HavePublicAddress());//initialize server
		MasterServer.RegisterHost(typeName, gameName);//register host
		Debug.Log(gameObject.GetComponent<NetworkView>().viewID);
		players = new ArrayList(); //initialize the arraylist that holds all the players
	}//end StartServer
	
	void OnMasterServerEvent(MasterServerEvent msEvent){
		if (msEvent == MasterServerEvent.HostListReceived){
			hostList = MasterServer.PollHostList ();
		}
	}//end onMasterServerEvent

	void OnServerInitialized(){
		message = "Server Initialized";//sets the message to be displayed
		InstshowMessage = true; //allows the message to be displayed
		this.Invoke ("stopIMessage", 5);//stops displaying the message after five seconds
		SpawnSPlayer();//spawns the instructor player (just a camera)
	}//end onServerInitialized
	
	private void SpawnSPlayer(){
		Network.Instantiate(instPrefab, new Vector3(0f, 5f, 0f), Quaternion.identity, 0);
	}//end spawnplayer

	[RPC]
	void displayStudentMessage(string info){
		message = info;
		InstshowMessage = true;
		this.Invoke ("stopIMessage", 5);//displays message for 5 seconds	
	}//end displayStudentMessage
	
	void messageStudents(){ //sends "Hello World" message to all clients
		Network.SetSendingEnabled (0, true);
		gameObject.AddComponent<StudentNetworkManager> ();
		Debug.Log (gameObject.GetComponent<StudentNetworkManager>());
		gameObject.GetComponent<NetworkView>().RPC ("displayMessage", RPCMode.Others, someInfo);
	}//end message Students


	void stopIMessage(){
		InstshowMessage = false;
	}//end stop message
	
	void OnGUI(){
		if (InstshowMessage) { //displays a message to the screen
			GUI.Label(new Rect(10f, 10f, 100f, 50f), message);
		}
		if (!Network.isClient && !Network.isServer){//if there is no network connection
			if (GUI.Button(new Rect(100, 100, 250, 100), "Start Server")){//display the button that initializes the server
				StartServer();
			}//end inner if
		}//end outer if
		if(Network.isServer){//if the server has been initialized, display instructor options
			if(GUI.Button(new Rect(100, 100, 250, 100), "Send message")){
				messageStudents();
			}
			if (GUI.Button(new Rect(400, 100, 250, 100), "Option1")){}
			if(GUI.Button(new Rect(100, 250, 250, 100), "Option2")){}
			if(GUI.Button(new Rect(400, 250, 250, 100), "Option3")){}
		}
	}//end onGUI

	// Update is called once per frame
	void Update (){}//end update
}//end class