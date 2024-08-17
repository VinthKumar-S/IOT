import 'dart:convert';
import 'package:http/http.dart' as http;

class weatherService{
  final String apiKey = '0354daa2c60949aca6cdb3edec91ae63';
  final String city = 'London';
  final String baseUrl = 'https://api.weatherbit.io/v2.0/current';

  Future<Map<String, dynamic>> fetchWeather() async{
    final url = '$baseUrl?city=$city&key=$apiKey';
    final response = await http.get(Uri.parse(url));

    if(response.statusCode == 200){
      return json.decode(response.body)['data'][0];
    }
    else{
      throw Exception("Failed to load weather data");
    }
  }
}
