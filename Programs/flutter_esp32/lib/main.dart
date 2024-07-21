import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'firebase_options.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:toggle_switch/toggle_switch.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {

    return MaterialApp(
      home: ledContainer(),
      debugShowCheckedModeBanner: false,
      theme: ThemeData.light(),
    );
 
  }
}

class ledContainer extends StatefulWidget {
  const ledContainer({super.key});

  @override
  State<ledContainer> createState() => _ledContainerState();
}

class _ledContainerState extends State<ledContainer> {
  
  FirebaseDatabase database = FirebaseDatabase.instance;
  final firebaseApp = Firebase.app();
  DatabaseReference ref = FirebaseDatabase.instance.ref();

  bool light = true;

  final MaterialStateProperty<Icon?> thumIcon = 
    MaterialStateProperty.resolveWith<Icon?>(
      (Set<MaterialState> states){
        if(states.contains(MaterialState.selected)){
          return const Icon(Icons.check);
        }
        return const Icon(Icons.close);
      }
    );
  @override
  Widget build(BuildContext context) {
    return  Scaffold(
        appBar: AppBar(
          backgroundColor: Colors.amber,
          title: Text("LED Controller"),
        ),
        body:Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                  /*  ToggleSwitch(
                    initialLabelIndex: 0,
                    totalSwitches: 2,
                    labels: ['On','OFF'],
                    onToggle: (index) async {
                      if(index == 0){
                        await ref.update({
                          "LED_STATUS" : "ON" 
                        });
                      }
                      else if(index == 1){
                          await ref.update({
                            "LED_STATUS" : "OFF" 
                          });
                      }
                    },),*/
                    Switch(
                      thumbIcon: thumIcon,
                      value: light, onChanged: (value) async{
                        setState(()  {
                          light = value;
                          //print(light);
                        });
                        if(value == true){
                          await ref.update({
                            "LED_STATUS" : "ON" 
                          });
                        }
                        else{
                          await ref.update({
                            "LED_STATUS" : "OFF" 
                          });
                        }
                      }
                    )
                  ],
                ),
          ],
        ),
          );
  }
}