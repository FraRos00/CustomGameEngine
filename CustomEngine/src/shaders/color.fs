#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 tint;   // colore da applicare (settabile da CPU)

out vec4 finalColor;

void main() {
    vec4 tex = texture(texture0, fragTexCoord);

    // Se il pixel è completamente trasparente → esci
   // if (tex.a == 0.0) {
   //   discard;
   //}

    // Colorazione: mantieni il colore della texture e moltiplicalo per il tint
    finalColor = vec4(tex.rgb * tint.rgb, tex.a * tint.a);
}
