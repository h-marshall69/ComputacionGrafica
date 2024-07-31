import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

camera.position.z = 15;

function createKochFractal(size, depth) {
    const group = new THREE.Group();

    if (depth === 0) {
        const geometry = new THREE.Geometry();
        geometry.vertices.push(
            new THREE.Vector3(-size / 2, -size / 2, 0),
            new THREE.Vector3(size / 2, -size / 2, 0),
            new THREE.Vector3(size / 2, size / 2, 0),
            new THREE.Vector3(-size / 2, size / 2, 0),
            new THREE.Vector3(-size / 2, -size / 2, 0)
        );
        const material = new THREE.LineBasicMaterial({ color: 0xff0000 });
        const line = new THREE.Line(geometry, material);
        group.add(line);
    } else {
        const newSize = size / 3;
        const positions = [
            [-newSize, -newSize, 0],
            [newSize, -newSize, 0],
            [newSize, newSize, 0],
            [-newSize, newSize, 0],
            [-newSize, -newSize, 0]
        ];

        for (let i = 0; i < positions.length - 1; i++) {
            const start = positions[i];
            const end = positions[i + 1];

            for (let j = 0; j < 3; j++) {
                const x = start[0] + (end[0] - start[0]) * (j / 3);
                const y = start[1] + (end[1] - start[1]) * (j / 3);

                const subFractal = createKochFractal(newSize, depth - 1);
                subFractal.position.set(x, y, 0);
                group.add(subFractal);
            }
        }
    }

    return group;
}

const fractal = createKochFractal(9, 3);
scene.add(fractal);

function animate() {
    fractal.rotation.x += 0.01;
    fractal.rotation.y += 0.01;
    renderer.render(scene, camera);
}
