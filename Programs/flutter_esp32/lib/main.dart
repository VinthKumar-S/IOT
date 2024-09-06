import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:flutter_esp32/motorController.dart';
import 'package:flutter_esp32/scheduleDates.dart';
import 'package:flutter_esp32/temperatureMeasurement.dart';
import 'package:workmanager/workmanager.dart';
import 'package:flutter_esp32/notificationSerivce.dart';
import 'firebase_options.dart';
import 'package:get/get.dart';
import 'bottomNavigator.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  Workmanager().initialize(callbackDispatcher);
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  runApp(MyApp());
}

void callbackDispatcher(){
  Workmanager().executeTask((taskName, inputData) async{
    await checkForUpcomingSchedule();

    return Future.value(true);
  });
}

Future<void> checkForUpcomingSchedule() async{
  var now = DateTime.now();
  QuerySnapshot snapshot = await FirebaseFirestore.instance.collection("Schedule").get();

  for(var doc in snapshot.docs){
    DateTime eventDate = (doc['eventDate'] as Timestamp).toDate();

    if(isSameDate(eventDate, now)){
      NotificationService().showNotification(title: '$doc[eventName]',body: 'It Works');
    }
  }
}

class MyApp extends StatelessWidget {
  MyApp({super.key});

    final bottomNavController controller = Get.put(bottomNavController());

  final List pages =[
     motorContainerState(),
     temperatureMeasureState(),
     scheduleDateState()
  ];

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {

    return GetMaterialApp(
      home: Obx(() => Scaffold(
        body: pages[controller.selectedIndex.value],
        bottomNavigationBar: BottomNavigationBar(
        currentIndex: controller.selectedIndex.value,
        onTap: controller.changeIndex,
        items: [
          BottomNavigationBarItem(
            icon:Icon(Icons.home), 
            label: 'Home'
          ),
          BottomNavigationBarItem(
            icon:Icon(Icons.beach_access_sharp), 
            label: 'Weather' 
          ),
          BottomNavigationBarItem(
            icon:Icon(Icons.calendar_today_sharp), 
            label:'Events' 
          ),
        ]
      ),
      )),
      debugShowCheckedModeBanner: false,
      theme: ThemeData.light(),
    );
 
  }
}
