using zadanie1.lib;

namespace zadanie1.Test;

[TestClass]
public sealed class TemperatureUnitsTests
{
    [TestMethod]
    public void CelsiusToFahrenheit()
    {
        Assert.AreEqual(32, TemperatureUnits.CelsiusToFahrenheit(0), 1e-7);
        Assert.AreEqual(212, TemperatureUnits.CelsiusToFahrenheit(100), 1e-7);
        Assert.AreEqual(-40, TemperatureUnits.CelsiusToFahrenheit(-40), 1e-7);

    }
}
