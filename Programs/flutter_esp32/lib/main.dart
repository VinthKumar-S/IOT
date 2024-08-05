import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'firebase_options.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:get/get.dart';


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

    return GetMaterialApp(
      home: _ledContainerState(),
      debugShowCheckedModeBanner: false,
      theme: ThemeData.light(),
    );
 
  }
}

class ledContainer extends GetxController{
  FirebaseDatabase database = FirebaseDatabase.instance;
  final firebaseApp = Firebase.app();
  DatabaseReference ref = FirebaseDatabase.instance.ref();
  // DatabaseReference refUltraSonic = FirebaseDatabase.instance.ref('ultraSonic');
  
  bool light = true.obs();

  var _hydration = 0.0.obs;

  //var data = <dynamic,dynamic>{}.obs;

  @override
  void onInit() {
    // TODO: implement onInit
    super.onInit();
    readData();
  }

  void readData(){
   /* refUltraSonic.once().then((DatabaseEvent event){
      DataSnapshot snapshot = event.snapshot;
       if(snapshot.exists){
        data.value = Map<dynamic, dynamic>.from(snapshot.value as Map);
       // print(data.value);
      }    
    });*/
    ref.onValue.listen((event) {
      final data = event.snapshot.value as Map<dynamic, dynamic>;
      _hydration.value = double.parse(data['Hydration']!);
    });
  }
}

class _ledContainerState extends StatelessWidget {

  final controller = Get.put(ledContainer());

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
          leading:  Switch(
                      thumbIcon: thumIcon,
                      value: controller.light, onChanged: (value) async{
                        if(value == true){
                          await controller.ref.update({
                            "LED_STATUS" : "ON" 
                          });
                        }
                        else{
                          await controller.ref.update({
                            "LED_STATUS" : "OFF" 
                          });
                        }
                      }
                    ) ,
        ),
        body: Obx(()
        {
            double hydroLevel=(controller._hydration.value/100);
            return Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Stack(
                  children: [
                    Center(
                      child: Container(
                      width: 180,
                      height: 180,
                      child: CircularProgressIndicator(
                        value:hydroLevel ,
                        strokeWidth: 10,
                        backgroundColor: Colors.yellow,
                        valueColor: AlwaysStoppedAnimation<Color>(Colors.purple),
                        
                        ),
                      ),
                    ),

                    Center(
                      child: Column(
                        children: [
                          SizedBox(height: 65,),
                          Text(
                            '$hydroLevel%'
                            ,style: TextStyle(
                              fontSize: 35
                            ),
                          ),
                        ],
                      ),
                    )
                  ],
                )
              ],
            );
        }
           /*if(false)
           {
              return Center(child: CircularProgressIndicator());
           }
           else 
           {

              return  Center(
                child: Column(
                  children: [
                      Text(""),
                  ],
                ),
              );
             /* var i=0;
              return ListView.builder(
                      shrinkWrap: true,
                      itemCount:controller.data.length,
                      itemBuilder: (context,index){
                        //print(controller.data.length);
                        i++;
                        String key = controller.data.keys.elementAt(index);
                        return ListTile(
                          title: Text('$i : ${controller.data[key]}'),
                        );
                      },  
              );*/
              
           }*/
        )
      );
  }
}