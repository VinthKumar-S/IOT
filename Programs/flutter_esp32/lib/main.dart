
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:flutter_esp32/motorController.dart';
import 'package:flutter_esp32/scheduleDates.dart';
import 'package:flutter_esp32/temperatureMeasurement.dart';
import 'firebase_options.dart';
import 'package:get/get.dart';
import 'bottomNavigator.dart';
import 'package:cron/cron.dart';
import 'package:flutter_esp32/notificationSerivce.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  final cron = Cron();
  final NotificationService notificationService = NotificationService();
   cron.schedule(Schedule.parse('1 * * * *'), () async{ 
      notificationService.showNotification(
          title: "Test",body:"Success"
        );
  });
  runApp(MyApp());
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
