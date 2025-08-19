#version 460 core
out vec4 FragColor;
in vec3 color;
in vec2 texCoord;

uniform float time;
uniform sampler2D samplera;
uniform sampler2D samplerb;
uniform sampler2D samplerc;

uniform float width;
uniform float height;

void main()
{
    //float intensity = (sin(time) + 1.0) / 2.0;
    //FragColor = vec4(color + intensity, 1.0f);
    //vec4 aColor = texture(samplera, texCoord);
    //vec4 vColor = texture(samplerb, texCoord);
    //vec4 cColor = texture(samplerc, texCoord);
    //float weight = cColor.r;
    
    //vec2 location = texCoord * vec2(width, height);
    //vec2 dx = dFdx(location);
    //vec2 dy = dFdy(location);
    // 计算梯度
    //float maxDelta = sqrt(max(dot(dx, dx) , dot(dy, dy)));
    //float L = log2(maxDelta);
    //int level = max(int(L+0.5), 0);

    FragColor = texture(samplera, texCoord);

    //vec4 finalColor = aColor * weight + vColor * (1.0 - weight);
    // mix() weight是第二个参数的权重，第一个参数是1-weight
    //vec4 finalColor = mix(aColor, vColor, weight);

    //FragColor = vec4(finalColor.rgb, 1.0);
}