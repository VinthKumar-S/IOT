import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
//import 'firebase_options.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:get/get.dart';
//import 'bottomNavigator.dart';


class motorContainer extends GetxController
{
  FirebaseDatabase database = FirebaseDatabase.instance;

  final firebaseApp = Firebase.app();

  DatabaseReference ref = FirebaseDatabase.instance.ref();

  bool light = true.obs();

  RxDouble _hydration = 0.0.obs;

  var isSelected = false.obs;

  @override
  void onInit() {
    // TODO: implement onInit
    super.onInit();
    readData();
  }

  void readData(){
    ref.onValue.listen((event) {
      final data = event.snapshot.value as Map<dynamic, dynamic>;
      _hydration.value = double.parse(data['Hydration']!);
    });
  }

  void toggleSelection(){
    isSelected.value = !isSelected.value;
  }

  void updateMotor(value) async{
    if(value){
      await ref.update({"Motor" : "ON"});
    }
    else{
      await ref.update({"Motor" : "OFF"});
    }
  }
}





class motorContainerState extends StatelessWidget {

  final motorContainer controller = Get.put(motorContainer());
  
  @override
  Widget build(BuildContext context) {
    
    return  Scaffold(
        appBar: AppBar(
          backgroundColor: Colors.amber,
          title: Text(
            "HOME",
            style: TextStyle(
              fontWeight: FontWeight.bold
            ),
            ),

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
                ),
                SizedBox(height:50,),
                Container(
                  width: 150,
                  height: 110,
                  decoration: BoxDecoration(
                    color: Colors.white,
                    //shape: BoxShape.circle,
                    borderRadius: BorderRadius.all(Radius.circular(20)),
                    boxShadow: [
                      BoxShadow(
                        color: Colors.grey,
                        blurRadius: 2.0
                      )
                    ]
                  ),
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                     // Icon(controller.thumIcon.icon),
                      Switch(
                        value: controller.isSelected.value, onChanged: (value) async{
                          controller.toggleSelection();
                          controller.updateMotor(value);
                        }
                      ),
                      Text(
                        "Motor",
                        style: TextStyle(
                          fontSize: 20
                        ),
                      )
                    ],
                  ),
                )
              ],
            );
        }
        ),
       // bottomNavigationBar: bottomNavBar(),
      );
  }
}