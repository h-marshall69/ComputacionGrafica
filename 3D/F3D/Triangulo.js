import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

camera.position.z = 15;

function createTetrahedronFractal(size, depth) {
    const group = new THREE.Group();
    
    if (depth === 0) {
        const geometry = new THREE.TetrahedronGeometry(size);
        const edges = new THREE.EdgesGeometry(geometry);
        const material = new THREE.LineBasicMaterial({ color: 0xff0000 });
        const line = new THREE.LineSegments(edges, material);
        group.add(line);
    } else {
        const newSize = size / 2;
        
        const positions = [
            [0, newSize, 0],
            [-newSize, -newSize, newSize],
            [newSize, -newSize, newSize],
            [0, -newSize, -newSize]
        ];

        for (const pos of positions) {
            const subFractal = createTetrahedronFractal(newSize, depth - 1);
            subFractal.position.set(...pos);
            group.add(subFractal);
        }
    }

    return group;
}

const fractal = createTetrahedronFractal(5, 4);
scene.add(fractal);

function animate() {
    //fractal.rotation.x += 0.01;
    fractal.rotation.y += 0.01;
    renderer.render(scene, camera);
}
