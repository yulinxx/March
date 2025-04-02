namespace IRender
{

    #include <cstddef>
    
    class IRenderInterface
    {

    public:
        IRenderInterface() = default;
        virtual ~IRenderInterface() = default;

    public:
        virtual void drawPoints(const float* points, size_t nPtsCount) = 0;

        virtual void drawLine(float* data, size_t nPtsCount) = 0;
        virtual void drawLines(float* data, size_t nPtsCount) = 0;

    };

}