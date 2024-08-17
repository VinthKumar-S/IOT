
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_esp32/weatherService.dart';
import 'package:get/get.dart';

class temperatureMeasure extends GetxController{
  var waatherData = {}.obs;
  var isLoading = true.obs;
  
  @override
  void onInit() {
    // TODO: implement onInit
    super.onInit();
    fetchWeather();
  }

  void fetchWeather() async{
    try{
      isLoading(true);
      var data = await weatherService().fetchWeather();
      waatherData.value = data;
    }
    finally {
      isLoading(false);
    }
  }
}

class temperatureMeasureState extends StatelessWidget {
  temperatureMeasureState({super.key});
  final temperatureMeasure controller = Get.put(temperatureMeasure());

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Weather Condition'),
      ),
      body: Center(
        child: Obx((){
          if(controller.isLoading.value){
            return CircularProgressIndicator();
          }
          else if(controller.waatherData.isEmpty){
            return Text('Failed to load data');
          }
          else{
            return Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Text(
                  '${controller.waatherData['city_name']}',
                )
              ],
            );
          }
        })
      ),
    );
  }
}