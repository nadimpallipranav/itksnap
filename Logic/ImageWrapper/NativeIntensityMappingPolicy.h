#ifndef NATIVEINTENSITYMAPPING_H
#define NATIVEINTENSITYMAPPING_H

/**
 * @brief The AbstractNativeIntensityMapping class
 * This class is the parent in a hierarchy of classes describing a mapping from
 * the internal datatype to the 'native' datatype. These mappings are used
 * in cases where the image is represented internally as a short type, although
 * the underlying data is in the reals.
 */
class AbstractNativeIntensityMapping
{
public:
  virtual double operator() (double g) const = 0;
  virtual double MapGradientMagnitudeToNative(double g) const = 0;
  virtual double MapInternalToNative(double g) const = 0;
  virtual double MapNativeToInternal(double g) const = 0;
};

class LinearInternalToNativeIntensityMapping : public AbstractNativeIntensityMapping
{
public:
  double operator() (double g) const
    { return MapInternalToNative(g); }

  double MapGradientMagnitudeToNative(double internalGM) const
    { return internalGM * scale; }

  double MapInternalToNative(double internal) const
    { return internal * scale + shift; }

  double MapNativeToInternal(double native) const
    { return (native - shift) / scale; }

  LinearInternalToNativeIntensityMapping() : scale(1.0), shift(0.0) {}
  LinearInternalToNativeIntensityMapping(double a, double b) : scale(a), shift(b) {}

private:
  double scale;
  double shift;
};

class IdentityInternalToNativeIntensityMapping : public AbstractNativeIntensityMapping
{
public:
  double operator() (double g) const
    { return g; }

  double MapGradientMagnitudeToNative(double internalGM) const
    { return internalGM; }

  double MapInternalToNative(double internal) const
    { return internal; }

  double MapNativeToInternal(double native) const
    { return native; }

};



#endif // NATIVEINTENSITYMAPPING_H