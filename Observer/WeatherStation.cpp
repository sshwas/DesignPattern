// "Head First Design Pattern" C++ implementation [Observer Pattern] : Publisher-Subscribe
// Define a one-to-many dependency between objects so that when an object's state changes,
// all objects that depend on it are notified and automatically refreshed.

#include <iostream>
#include <set>
using namespace std;

//interface
class Observer
{
public:
	virtual void update(float temperature, float humidity, float pressure) = 0;
};

class DisplayElement
{
public:
	virtual void display() = 0;
};

class Subject
{
public:
	virtual void RegisterObserver(Observer *p_observer) = 0;
	virtual void RemoveObserver(Observer *p_observer) = 0;
	virtual void NotifiyObserver() = 0;
};

//object
class WeatherData : public Subject
{
private:
	set<Observer *> observers;
	float temperature;
	float humidity;
	float pressure;

public:
	WeatherData(){}

	void RegisterObserver(Observer *p_observer)
	{
		observers.insert(p_observer);
	}

	void RemoveObserver(Observer *p_observer)
	{
		observers.erase(p_observer);
	}

	void NotifiyObserver()
	{
		//Traversing all observer updates
		set<Observer *>::iterator it;
		for (it = observers.begin(); it != observers.end(); ++it)
		{
			(*it)->update(temperature, humidity, pressure);
		}
	}

	void GetTemperature();
	void GetHumidity();
	void GetPressure();

	void MeasurementsChanged()
	{
		NotifiyObserver();
	}

	void SetMeasurements(float temperature, float humidity, float pressure)
	{
		this->temperature = temperature;
		this->humidity = humidity;
		this->pressure = pressure;
		MeasurementsChanged();
	}
};

class CurrentConditionsDisplay : public Observer, public DisplayElement
{
private:
	WeatherData *p_weather_data;
	float temperature;
	float humidity;
	float pressure;

public:
	CurrentConditionsDisplay(WeatherData *p_weather_data)
	{
		this->p_weather_data = p_weather_data;
		//subscription
		this->p_weather_data->RegisterObserver(this);
	}

	~CurrentConditionsDisplay()
	{
		//unsubscribe
		this->p_weather_data->RemoveObserver(this);
	}

	void update(float temperature, float humidity, float pressure)
	{
		this->temperature = temperature;
		this->humidity = humidity;
		this->pressure = pressure;
		display();
	}

	void display()
	{
		printf("CurrentConditionsDisplay -> temperature:%.2f, humidity:%.2f, pressure:%.2f \n", temperature, humidity, pressure);
	}
};

class StatisticsDisplay : public Observer, public DisplayElement
{
private:
	WeatherData *p_weather_data;
	float temperature;
	float humidity;
	float pressure;

public:
	StatisticsDisplay(WeatherData *p_weather_data)
	{
		this->p_weather_data = p_weather_data;
		//subscription
		this->p_weather_data->RegisterObserver(this);
	}

	~StatisticsDisplay()
	{
		//unsubscribe
		this->p_weather_data->RemoveObserver(this);
	}

	void update(float temperature, float humidity, float pressure)
	{
		this->temperature = temperature;
		this->humidity = humidity;
		this->pressure = pressure;
		display();
	}

	void display()
	{
		printf("StatisticsDisplay -> temperature:%.2f, humidity:%.2f, pressure:%.2f \n", temperature, humidity, pressure);
	}
};

int main()
{
	WeatherData *p_weather_data = new WeatherData();
	CurrentConditionsDisplay *p_current_display = new CurrentConditionsDisplay(p_weather_data);
	StatisticsDisplay *p_statistics_display = new StatisticsDisplay(p_weather_data);

	p_weather_data->SetMeasurements(80, 65, 30.4f);
	p_weather_data->SetMeasurements(81, 72, 32.4f);

	p_current_display->~CurrentConditionsDisplay();//unsubscribe
	p_weather_data->SetMeasurements(79.5, 68, 34.2f);

	return 0;
}